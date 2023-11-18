// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLVAO.h"
#include <cassert>

void gl::VAO::create() {
	assert(isEmpty());

	glGenVertexArrays(1, &m_id);
}

void gl::VAO::release() {
	assert(!isEmpty());

	glDeleteVertexArrays(1, &m_id);
	m_id = 0;
}

void gl::VAO::bind() {
	assert(!isEmpty());

	glBindVertexArray(m_id);
}

void gl::VAO::unbind() {
	glBindVertexArray(0);
}
