// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLEBO.h"

void gl::EBO::setData(const Indices& data, const GLenum usage) {
	assert(!isEmpty());

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), usage);
}

void gl::EBO::bind() {
	assert(!isEmpty());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void gl::EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
