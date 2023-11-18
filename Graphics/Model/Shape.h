// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Direction.h"
#include "ShapeId.h"
#include "Mesh.h"

/*
*	Shape(.h/.cpp) contains a class that implements the creation of templated shape.
* 
*	Usage:
*		Shape shape(-some id-, -some tex coords-);
* 
*		Mesh shapeModel = shape.createMesh(...);
*/

namespace model {
	class Shape final {
	private:
		ShapeId m_id;
		gl::Vertices m_texCoords;

	private:
		constexpr Shape(const ShapeId id)
			: m_id(id) { }

	public:
		constexpr Shape(const ShapeId id, gl::Vertices texCoords)
			: m_id(id), m_texCoords(std::move(texCoords)) { }

		Mesh createMesh(); // for those without parameters
		Mesh createMesh(const glm::vec3& from, const glm::vec3& to); // for a quad and box
		Mesh createMesh(const math::DirectionFlag flags); // for those with direction flags
		Mesh createMesh(const float width, const float height, const float depth); // for those with direction flags
	};
}
