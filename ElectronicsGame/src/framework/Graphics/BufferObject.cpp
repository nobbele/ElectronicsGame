#include <Graphics/BufferObject.h>

#include <GL/gl3w.h>

BufferObject::BufferObject(GLenum type, GLsizei size) {
	this->m_type = type;
	this->m_size = size;
	glGenBuffers(this->m_size, &this->m_bo);
}
BufferObject::~BufferObject() {
	glDeleteBuffers(this->m_size, &this->m_bo);
}

void BufferObject::Bind() const {
	glBindBuffer(this->m_type, this->m_bo);
}