#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl3w.h>
#include <eg_containers.h>

class Texture {
	GLuint m_texture;
public:
	Vector2<int> size;

	Texture(const char *path);

	void Bind() const;
};

#endif