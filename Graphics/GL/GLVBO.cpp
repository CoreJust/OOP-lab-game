// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLVBO.h"

void gl::VBO::setData(const Vertices& data, const GLenum usage) {
	assert(!isEmpty());

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), usage);
}

void gl::VBO::setVertexAttribute(GLuint vboCount, const GLint dim) {
	glVertexAttribPointer(vboCount, dim, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(vboCount);
}

void gl::VBO::bind() {
	assert(!isEmpty());

	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void gl::VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
