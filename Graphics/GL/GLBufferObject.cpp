// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GLBufferObject.h"

void gl::BufferObject::create() {
	assert(m_isEmpty);

	glGenBuffers(1, &m_id);
	m_isEmpty = false;
}

void gl::BufferObject::release() {
	assert(!m_isEmpty);

	glDeleteBuffers(1, &m_id);
	m_isEmpty = true;
}
