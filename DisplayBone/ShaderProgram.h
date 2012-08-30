/*
Filename:	ShaderProgram.h
Author:	Nikolaus Karpinsky
Date Created:	09/20/10
Last Edited:	09/20/10

Revision Log:
09/20/10 - Nik Karpinsky - Original creation.
10/27/10 - Nik Karpinsky - Allows for VRJ context specific data
*/

#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

//#include <GL/glu.h>
//#include <GL/gl.h>

#include "PVRShell.h"
#include "OGLES2Tools.h" 

#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Shader.h"

using namespace std;

class ShaderProgram
{
    private:
        GLuint m_shaderID;
        vector<Shader*> m_shaders;

    public:
        ShaderProgram();
        ~ShaderProgram();
        void init();
        void attachShader(Shader *shader);
        bool link();

        void bind();
        void unbind();

        void uniform(const string name, const int data);
        void uniform(const string name, const float data);
        void uniform(const string name, const float* data, int count);
        void uniformMat4(const string name, GLboolean transpose, const GLfloat *value);
        void bindAttributeLocation(const string name, const GLuint index);

    private:
        bool _validateProgram(GLuint program);
};

#endif	// _WRENCH_GL_SHADER_PROGRAM_H_
