// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "GLObject.h"

/*
*	GLVAO.h contains a class that manages VAO.
*
*	VAO stands for Vertex Array Object - the state of a model.
*	It manages the attributes of the vertices.
*/

namespace gl {
	// Vertex Array Object
	class VAO final : public Object {
	public:
		void create() override;
		void release() override;

		void bind() override;
		void unbind() override;
	};
}