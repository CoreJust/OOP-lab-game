// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLVAO.h"
#include <cassert>

void gl::VAO::create() {
	assert(m_isEmpty);

	glGenVertexArrays(1, &m_id);
	m_isEmpty = false;
}

void gl::VAO::release() {
	assert(!m_isEmpty);

	glDeleteVertexArrays(1, &m_id);
	m_isEmpty = true;
}

void gl::VAO::bind() {
	assert(!m_isEmpty);

	glBindVertexArray(m_id);
}

void gl::VAO::unbind() {
	glBindVertexArray(0);
}
