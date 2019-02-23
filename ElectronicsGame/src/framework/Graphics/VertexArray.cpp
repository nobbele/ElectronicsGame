#include <Graphics/VertexArray.h>

#include <GL/gl3w.h>

VertexArray::VertexArray(float vertices[],  GLsizei size) {
    this->m_size = size;
	glGenVertexArrays(this->m_size, &this->m_va);
}
VertexArray::~VertexArray() {
    glDeleteVertexArrays(this->m_size, &this->m_va);
}

void VertexArray::Bind() const {
	glBindVertexArray(this->m_va);
}