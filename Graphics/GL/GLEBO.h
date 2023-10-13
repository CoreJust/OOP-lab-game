// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "GLBufferObject.h"

namespace gl {
	// Element Buffer Object is a set of indices to reduce memory usage of VBO
	// It allows to reuse a single vertex as much as we want
	class EBO final : public BufferObject {
	public:
		void setData(const Indices& data, const GLenum usage = GL_STATIC_DRAW);

		void bind() override;
		void unbind() override;
	};
}