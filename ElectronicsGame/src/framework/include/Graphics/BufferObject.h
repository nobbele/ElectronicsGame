#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include <GL/gl3w.h>

struct BufferObject {
	GLuint m_bo;
	GLsizei m_size;
	GLenum m_type;
public:
	BufferObject(GLenum type, GLsizei size=1);
	~BufferObject();

	void Bind() const;

	template<typename T>
	void Data(GLsizeiptr size, const T data[], GLenum usage) const {
		glBufferData(this->m_type, size, data, usage);
	}
};

#endif