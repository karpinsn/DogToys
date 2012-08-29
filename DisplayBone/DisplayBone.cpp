#include <stdio.h>
#include <stddef.h>

// Needed for OpenGLES 2.0 stuff
#include "PVRShell.h"

///////////////////////////////////////////////////////////////////////////
//	Class: FringeDisplay
//
//	Summary: Class that displays the fringe at full screen. Needs to 
//	         inherit from PVR since that provides our rendering context
//////////////////////////////////////////////////////////////////////////
class FringeDisplay : public PVRShell
{
	private:
		// Texture and VBO used to display the fringe
		GLuint m_fringeTexture;
		GLuint m_fringeVBO;

		// Shader used to display the texture
		GLuint m_fringeShader;

		// Locations of the data in the shader program
		GLint m_vertLoc;
		GLint m_texLoc;
	public:
		// PVRShell Functions
		virtual bool InitApplication();
		virtual bool InitView();
		virtual bool ReleaseView();
		virtual bool QuitApplication();
		virtual bool RenderScene();
};

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
	return true;
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
	
	//TODO - Need to load the shaders

	/////////////////////////////////////////////////
	// Cache our fullscreen quad
	/////////////////////////////////////////////////
	// Grab the locations of our attributes in the shaders
	GLint m_vertLoc = glGetAttribLocation(m_fringeShader, "vert");
	GLint m_texLoc  = glGetAttribLocation(m_fringeShader, "texCoord");

	// Cache the geometry (held in fullscreenQuad)
	glGenBuffer(1, &m_fringeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_fringeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullscreenQuad), &fullscreenQuad[0], GL_STATIC_DRAW);
	glVertexAttribPointer(m_vertLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position);
	glVertexAttribPointer(m_texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, tex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/////////////////////////////////////////////////
	// Load the fringe image
	/////////////////////////////////////////////////
	glGenTextures(1, m_fringeTexture);
	glBindTexture(GL_TEXTURE_2D, m_fringeTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// TODO - Need to load the image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	return true;
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

	//TODO - Delete the shader

	return true;
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

	// By returning true, we signify to PVR that all
	// went well and that it can flip our buffers
	return true;
}

bool FringeDisplay::QuitApplication()
{
	// Not much to do...
	return true;
}
