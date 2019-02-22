#include <Graphics/Shader.h>

#include <stdio.h>
#include <IO/eg_error.h>

Shader::Shader(const char *vertexSource, const char *fragmentSource) {
	#define GL_vertex_SHADER GL_VERTEX_SHADER
	#define GL_fragment_SHADER GL_FRAGMENT_SHADER
	#define shader(type) {\
		this-> type ## Shader = glCreateShader(GL_ ## type ## _SHADER);\
		glShaderSource(this-> type ## Shader, 1, & type ## Source, NULL);\
		glCompileShader(this-> type ## Shader);\
		/* check for shader compile  */\
		GLint success;\
		glGetShaderiv(this-> type ## Shader, GL_COMPILE_STATUS, &success);\
		if (!success)\
		{\
			EG_ERROR(\
				printf("%s\n", type ## Source);\
				char infoLog[512];\
				glGetShaderInfoLog(this-> type ## Shader, 512, NULL, infoLog);\
				fprintf(stderr, "Shader compilation failed %s", infoLog);\
			);\
		}\
	}
	shader(fragment);
	shader(vertex);
	#undef shader
}
Shader::~Shader() {
	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragmentShader);
}