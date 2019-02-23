#include <Graphics/ShaderProgram.h>

#include <stdio.h>
#include <IO/eg_error.h>
#include <IO/eg_io.h>

ShaderProgram::ShaderProgram(Shader &shader) {
	this->m_program = glCreateProgram();
    glAttachShader(this->m_program, shader.vertexShader);
    glAttachShader(this->m_program, shader.fragmentShader);
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

ShaderProgram *ShaderProgram::NewFromFile(const char *vertex_file, const char *fragment_file) {
    char *vertex_source = readFile(vertex_file);
	char *fragment_source = readFile(fragment_file);
	Shader shader(vertex_source, fragment_source);
	delete vertex_source;
	delete fragment_source;
    return new ShaderProgram(shader);
}

void ShaderProgram::Use() const {
	glUseProgram(this->m_program);
}

GLint ShaderProgram::GetUniformLocation(const char *name) const {
    GLint location = glGetUniformLocation(this->m_program, name);
    if(location == -1) {
        EG_ERROR(
			fprintf(stderr, "Couldn't get vertexPositions uniform location")
		);
    }
	return location;
}