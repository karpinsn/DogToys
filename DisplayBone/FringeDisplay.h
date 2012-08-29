#ifndef _FRINGE_DISPLAY_H_
#define _FRINGE_DISPLAY_H_

#include <stdio.h>
#include <stddef.h>

// OpenGL Includes
#include <GL/gl.h>
#include <GL/glu.h>

// Helper classes
#include "PNGLoader.h"

// Needed for OpenGLES 2.0 stuff
#include "PVRShell.h"

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
		unique_ptr<ShaderProgram> m_fringeShader;

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

#endif // _FRINGE_DISPLAY_H_
