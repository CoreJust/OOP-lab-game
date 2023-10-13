// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "GLBufferObject.h"

namespace gl {
	// Vertex Buffer Object is what can be called a "mesh" of an object
	class VBO final : public BufferObject {
	public:
		void setData(const Vertices& data, const GLenum usage = GL_STATIC_DRAW);

		void bind() override;
		void unbind() override;
	};
}