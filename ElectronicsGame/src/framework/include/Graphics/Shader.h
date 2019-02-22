#ifndef SHADER_H
#define SHADER_H

#include <GL/gl3w.h>

class ShaderProgram;
#include <Graphics/ShaderProgram.h>

class Shader {
public:
	GLuint vertexShader;
	GLuint fragmentShader;

	Shader(const char *vertSource, const char *fragmentSource);
	~Shader();
};

#endif