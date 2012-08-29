#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    m_shaderID = 0;
}

ShaderProgram::~ShaderProgram()
{
    for(vector<Shader*>::iterator itr = m_shaders.begin(); itr != m_shaders.end(); ++itr)
    {
        glDetachShader(m_shaderID, (*itr)->shaderID());
        delete *itr;
    }

    glDeleteProgram(m_shaderID);
}

void ShaderProgram::init()
{
    m_shaderID = glCreateProgram();    
}

void ShaderProgram::attachShader(Shader *shader)
{
    glAttachShader(m_shaderID, shader->shaderID());
}

void ShaderProgram::bind()
{
    glUseProgram(m_shaderID);
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

bool ShaderProgram::link()
{
    glLinkProgram(m_shaderID);

    return _validateProgram(m_shaderID);
}

void ShaderProgram::uniform(const string name, const int data)
{
    bind();
    GLuint location = glGetUniformLocation(m_shaderID, name.c_str());
    glUniform1i(location, data);
}

void ShaderProgram::uniform(const string name, const float data)
{
    bind();
    GLuint location = glGetUniformLocation(m_shaderID, name.c_str());
    glUniform1f(location, data);
}

void ShaderProgram::uniform(const string name, const float* data, int count)
{
    bind();
    GLuint location = glGetUniformLocation(m_shaderID, name.c_str());
    glUniform1fv(location, count, data);
}

void ShaderProgram::uniform(const string name, const glm::vec3 data)
{
    bind();
    GLuint location = glGetUniformLocation(m_shaderID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(data));
}

void ShaderProgram::uniform(const string name, const glm::vec4 data)
{
    bind();
    GLuint location = glGetUniformLocation(m_shaderID, name.c_str());
    glUniform4fv(location, 1, glm::value_ptr(data));
}

void ShaderProgram::uniform(const string name, const glm::mat3 data)
{
    bind();
    GLuint location = glGetUniformLocation(m_shaderID, name.c_str());
    glUniformMatrix3fv(location, 1, false, glm::value_ptr(data));
}

void ShaderProgram::uniform(const string name, const glm::mat4 data)
{
    bind();
    GLuint location = glGetUniformLocation(m_shaderID, name.c_str());
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(data));
}

void ShaderProgram::bindAttributeLocation(const string name, GLuint index)
{
    glBindAttribLocation(m_shaderID, index, name.c_str());
}

bool ShaderProgram::_validateProgram(GLuint program)
{
    bool validProgram = false;

    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

    if (length <= 0)
    {
        glValidateProgram(program);
        GLint status;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

        validProgram = status != GL_FALSE;
        if (!validProgram)
        {
            printf("Error validating shader program");
        }
    }
    else
    {
        printf("Shader program link error: ");
    }

    return validProgram;
}
