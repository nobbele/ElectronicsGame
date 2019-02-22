#include <Graphics/ShaderProgram.h>

#include <stdio.h>
#include <IO/eg_error.h>

ShaderProgram::ShaderProgram(Shader *shader) {
	this->m_program = glCreateProgram();
    glAttachShader(this->m_program, shader->vertexShader);
    glAttachShader(this->m_program, shader->fragmentShader);
    glLinkProgram(this->m_program);
    // check for linking errors
	GLint success;
    glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
    if (!success) {
        EG_ERROR(
            char infoLog[512];
            glGetProgramInfoLog(this->m_program, 512, NULL, infoLog);
            fprintf(stderr, "Shader compilation failed %s", infoLog);
        );
    }
}

void ShaderProgram::Use() {
	glUseProgram(this->m_program);
}

GLint ShaderProgram::GetUniformLocation(const char *name) {
	return glGetUniformLocation(this->m_program, name);
}