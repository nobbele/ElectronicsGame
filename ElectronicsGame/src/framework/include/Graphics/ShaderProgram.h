#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/gl3w.h>

struct Shader;
#include <Graphics/Shader.h>

class ShaderProgram {
	GLuint m_program;
public:
	ShaderProgram(Shader &shader);
	static ShaderProgram *NewFromFile(const char *vertex_file, const char *fragment_file);

	void Use() const;
	GLint GetUniformLocation(const char *name) const;
};

#endif