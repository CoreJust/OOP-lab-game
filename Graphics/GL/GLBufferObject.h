// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>

#include "GLObject.h"

/*
*	GLBufferObject.h contains a base class for all the opengl buffer objects.
*
*	A buffer object is an object that contains a sequence of some values
*	that are used for quick access without recalculation.
*/

namespace gl {
	using Vertices = std::vector<GLfloat>;
	using Indices = std::vector<GLuint>;

	// Base class for all the buffer objects (*BO)
	class BufferObject : public Object {
	public:
		void create() override final;
		void release() override final;
	};
}