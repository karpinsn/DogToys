#include <cstddef>
#include <memory>
#include <cstdio>

// Helper classes
#include "PNGLoader.h"
#include "ShaderProgram.h"
#include "Shader.h"

// Needed for OpenGLES 2.0 stuff
#include "PVRShell.h"
#include "OGLES2Tools.h" 

using namespace std;

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
        GLuint m_textureVertShader;
        GLuint m_textureFragShader;
        GLuint m_textureShader;
        
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

    private:
        bool _checkGLErrors();
};

// Struct representing the data we are sending to the GPU
typedef struct
{
	GLfloat position[3];
	GLfloat tex[2];
} Vertex;

// Actual data we are sending to the GPU
static Vertex fullscreenQuad[4]; 

// Source and binary shaders                                                    
const char c_szFragShaderSrcFile[]  = "TextureDisplay.fsh";                         
const char c_szFragShaderBinFile[]  = "TextureDisplay.fsc";                         
const char c_szVertShaderSrcFile[]  = "TextureDisplay.vsh";                         
const char c_szVertShaderBinFile[]  = "TextureDisplay.vsc";

// Called once per application run
bool FringeDisplay::InitApplication()
{
    fullscreenQuad[0].position[0] = -1.0f; fullscreenQuad[0].position[1] = -1.0f; fullscreenQuad[0].position[2] = 0.0f;
    fullscreenQuad[1].position[0] =  1.0f; fullscreenQuad[1].position[1] = -1.0f; fullscreenQuad[1].position[2] = 0.0f;
	fullscreenQuad[2].position[0] =  1.0f; fullscreenQuad[2].position[1] =  1.0f; fullscreenQuad[2].position[2] = 0.0f;
	fullscreenQuad[3].position[0] = -1.0f; fullscreenQuad[3].position[1] =  1.0f; fullscreenQuad[3].position[2] = 0.0f;

	fullscreenQuad[0].tex[0] = 0.0f; fullscreenQuad[0].tex[1] = 0.0f;
	fullscreenQuad[1].tex[0] = 1.0f; fullscreenQuad[1].tex[1] = 0.0f;
	fullscreenQuad[2].tex[0] = 1.0f; fullscreenQuad[2].tex[1] = 1.0f;
	fullscreenQuad[3].tex[0] = 0.0f; fullscreenQuad[3].tex[1] = 1.0f;

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
    CPVRTString* pErrorStr;
        
    if(PVRTShaderLoadFromFile(c_szVertShaderBinFile, c_szVertShaderSrcFile, GL_VERTEX_SHADER, GL_SGX_BINARY_IMG, &m_textureVertShader, pErrorStr) != PVR_SUCCESS)
    {                                                                           
        return false;                                                           
    }                                                                           
                                                                                    
    if (PVRTShaderLoadFromFile(c_szFragShaderBinFile, c_szFragShaderSrcFile, GL_FRAGMENT_SHADER, GL_SGX_BINARY_IMG, &m_textureFragShader, pErrorStr) != PVR_SUCCESS)
    {                                                                           
        return false;                                                           
    }     
    
    const char* aszAttribs[] = { "vertVertex", "vertTexCoord" };
                                                                                    
    if(PVRTCreateProgram(&m_textureShader, m_textureVertShader, m_textureFragShader, aszAttribs, 2, pErrorStr) != PVR_SUCCESS)
    {                                                                           
       return false;                                                           
    }                                                                           
    // Set the sampler2D variable to the first texture unit                     
    glUniform1i(glGetUniformLocation(m_textureShader, "Texture"), 0);
            
	/////////////////////////////////////////////////
	// Cache our fullscreen quad
	/////////////////////////////////////////////////
	// Cache the geometry (held in fullscreenQuad)
	glGenBuffers(1, &m_fringeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_fringeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullscreenQuad), &fullscreenQuad[0], GL_STATIC_DRAW);
	// Locations (first argument) set above when creating the shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    //  If we have OpenGL errors stop and notify of problems
    if(_checkGLErrors())
        return false;

	/////////////////////////////////////////////////
	// Load the fringe image
	/////////////////////////////////////////////////
    int width;
    int height;
	m_fringeTexture = PNGLoader::loadTexture("fringe.png", width, height);
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
	glDeleteTextures(1, &m_fringeTexture);
    

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
    glUseProgram(m_textureShader);	
		
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
        //  TODO- Comeback and find the PowerVR equalivalent of gluErrorString
        printf("OpenGL Error:\n"); 
        //printf("OpenGL Error: %s\n", gluErrorString(glError));
        return true;
    }

    return false;
}

/*!**************************************************************************** 
 *  @Function      NewDemo                                                         
 *   @Return        PVRShell*       The demo supplied by the user                   
 *    @Description   This function must be implemented by the user of the shell.     
 *                    The user should return its PVRShell object defining the         
 *                                    behaviour of the application.                                     
 ******************************************************************************/ 
PVRShell* NewDemo()                                                             
{                                                                               
    return new FringeDisplay();                                               
}
