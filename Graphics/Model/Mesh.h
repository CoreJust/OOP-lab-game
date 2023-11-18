// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <glm/glm.hpp>

#include "Utils/Result.h"
#include "Graphics/GL/GLBufferObject.h"

/*
*	Mesh(.h/.cpp) contains a struct that aggregates the components of a mesh.
*
*	A mesh is a set of vertices, indices and texture coords of the corresponding vertices.
*	Optionally, it can have additional characteristics such as light map, but that is not used
*	right now.
*/

namespace model {
	struct Mesh {

		///  Fields  ///

		gl::Vertices vertices;
		gl::Vertices texCoords; // Texture coordinates of the vertices
		gl::Indices indices;


		///  Methods  ///

		Mesh& optimize(); // Deletes excess vertices

		Mesh& mergeWith(const Mesh& other);
		Mesh& setTexCoords(gl::Vertices texCoords);

		Mesh& reverseIndices(); // For correct CULL_FACE, reverses the traversal order
		
		Mesh& move(const glm::vec3& shift);
		Mesh& rotate(const glm::vec3& angles);
		Mesh& rotateAround(const glm::vec3& center, const glm::vec3& angles);
		Mesh& scale(const float factor);

		utils::Result<utils::Void> validate(); // Checks for the valid mesh

		constexpr size_t getVerticesCount() const {
			return vertices.size() / 3;
		}
	};
}