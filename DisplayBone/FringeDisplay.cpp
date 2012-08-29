#include "FringeDisplay.h"

// Struct representing the data we are sending to the GPU
typedef struct
{
	GLfloat position[3];
	GLfloat tex[2];
} Vertex;

// Actual data we are sending to the GPU
static Vertex fullscreenQuad[] = 
{
	{
		.position = {-1.0f, -1.0f, 0.0f},
		.tex = {0.0f, 0.0f},
	},
	{
		.position = {1.0f, -1.0f, 0.0f},
		.tex = {1.0f, 0.0f},
	},
	{
		.position = {1.0f, 1.0f, 0.0f},
		.tex = {1.0f, 1.0f},
	},
	{
		.position = {-1.0f, 1.0f, 0.0f},
		.tex = {0.0f, 1.0f},
	},
};

// Called once per application run
bool FringeDisplay::InitApplication()
{
	// Not much to do ...
	return !_checkGLErrors();
}

// Called when there is a change to the rendering context
bool FringeDisplay::InitView()
{
	// Basic OpenGL setup
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	/////////////////////////////////////////////////
	// Need to load our shaders
	/////////////////////////////////////////////////
    m_fringeShader = unique_ptr<ShaderProgram>(new ShaderProgram());
    m_fringeShader->init();
    m_fringeShader->attachShader(new Shader(GL_VERTEX_SHADER, "Shaders/TextureDisplay.vert"));
    m_fringeShader->attachShader(new Shader(GL_FRAGMENT_SHADER, "Shaders/TextureDisplay.frag"));
    m_fringeShader->bindAttributeLocation("vert", 0);
    m_fringeShader->bindAttributeLocation("vertTexCoord", 1);
    m_fringeShader->link();
    m_fringeShader->uniform("texture", 0);

	/////////////////////////////////////////////////
	// Cache our fullscreen quad
	/////////////////////////////////////////////////
	// Cache the geometry (held in fullscreenQuad)
	glGenBuffer(1, &m_fringeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_fringeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullscreenQuad), &fullscreenQuad[0], GL_STATIC_DRAW);
	// Locations (first argument) set above when creating the shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, tex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    //  If we have OpenGL errors stop and notify of problems
    if(_checkGLErrors())
        return false;

	/////////////////////////////////////////////////
	// Load the fringe image
	/////////////////////////////////////////////////
    int width;
    int height;
	m_fringeTexture = PNGLoader.loadTexture("fringe.png", width, height);
    //  Make sure we didn't have any errors loading the fringe
    if(TEXTURE_LOAD_ERROR == m_fringeTexture) 
        return false;

    //  If we dont have any errors then we have sucessfully initialized
	return !_checkGLErrors();
}

// Called when there is a change in the rendering context 
// or before the application quits
bool FringeDisplay::ReleaseView()
{
	/////////////////////////////////////////////////
	// Release our VBO, Texture, and Shader
	/////////////////////////////////////////////////
	glDeleteBuffers(1, &m_fringeVBO);
	glDeleteTextures(1, m_fringeTexture);
    m_fringeShader.release();

	return !_checkGLErrors();
}

bool FringeDisplay::RenderScene()
{
	// Standard OpenGL stuff - Clear old buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////////////////////////////////////////////////	
	// Draw our full screen quad
	/////////////////////////////////////////////////
	// Bind our shader
	glUseProgram(m_fringeShader);
		
	// Enable and bind our fringe texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fringeTexture);

	// Enable our data
	glEnableVertexAttribArray(m_vertLoc);
	glEnableVertexAttribArray(m_texLoc);

	// Draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Unbind 
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(m_vertLoc);
	glDisableVertexAttribArray(m_texLoc);
	glUseProgram(0);	

    // Make sure we dont have errors.
	// By returning true, we signify to PVR that all
	// went well and that it can flip our buffers.
	return !_checkGLErrors();
}

bool FringeDisplay::QuitApplication()
{
	// Not much to do...
	return !_checkGLErrors();
}

bool FringeDisplay::_checkGLErrors()
{
    GLenum glError = glGetError();
    if(GL_NO_ERROR != glError)
    {
        printf("OpenGL Error: %s\n", gluErrorString(glError));
        return true;
    }

    return false;
}
