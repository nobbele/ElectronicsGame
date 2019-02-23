#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/gl3w.h>

class VertexArray {
	GLuint m_va;
    GLsizei m_size;
public:
	VertexArray(float vertices[], GLsizei size = 1);
    ~VertexArray();

	void Bind() const;
};

#endif