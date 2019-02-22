#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl3w.h>

class Texture {
	GLuint m_texture;
public:
	Texture(const char *path);

	void Bind();
};

#endif