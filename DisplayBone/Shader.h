/*
Filename:		Shader.h
Author:		    Nikolaus Karpinsky
Date Created:	09/20/10
Last Edited:	09/20/10

Revision Log:
09/20/10 - Nik Karpinsky - Original creation.
10/27/10 - Nik Karpinsky - Allows for VRJ context specific data
*/

#ifndef _SHADER_H_
#define _SHADER_H_

//#include <GL/gl.h>
//#include <GL/glu.h>

#include "PVRShell.h"
#include "OGLES2/OGLES2Tools.h" 

#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Shader 
{
    private:
        GLuint m_shaderID;

    public:
        Shader();
        Shader(GLenum shaderType, const string &filename);
        ~Shader();

        bool init(GLenum shaderType, const string &filename);

        GLuint shaderID(void);

    private:
        char* _loadShaderSource(const string &filename);
        bool _validateShader(GLuint shader, const string &filename);
};



#endif	// _SHADER_H_
