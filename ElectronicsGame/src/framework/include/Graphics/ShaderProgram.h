#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/gl3w.h>

struct Shader;
#include <Graphics/Shader.h>

class ShaderProgram {
	GLuint m_program;
public:
	ShaderProgram(Shader *shader);

	void Use();
	GLint GetUniformLocation(const char *name);
};

#endif