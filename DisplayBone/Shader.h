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

#include <GL/gl.h>
#include <GL/glu.h>

#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

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
