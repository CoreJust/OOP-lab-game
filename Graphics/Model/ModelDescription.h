// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <glm/glm.hpp>

#include "Math/Direction.h"
#include "ShapeId.h"
#include "Mesh.h"

/*
*	ModelDescription.h contains a class that allows to conveniently define a model
*	description that can be used to create a corresponding model.
*/

namespace model {
	class ModelDescription final {
	private:
		ShapeId m_id;
		union {
			math::DirectionFlag m_asDirectionFlags;
			glm::vec3 m_asFromTo[2];
			glm::vec3 m_asWHD; // width, height, depth
		};

	public:
		constexpr ModelDescription() noexcept : m_id(ShapeId::EMPTINESS) { }
		constexpr ModelDescription(const ShapeId id) noexcept
			: m_id(id) {
			assert(m_id == ShapeId::EMPTINESS || m_id == ShapeId::FLAT_FLOOR || m_id == ShapeId::FLAT_FLOOR_OBJECT);
		}

		constexpr ModelDescription(const ShapeId id, const math::DirectionFlag flags)
			: m_id(id), m_asDirectionFlags(flags) {
			assert(m_id == ShapeId::SIMPLE_WALL);
		}

		constexpr ModelDescription(const ShapeId id, const glm::vec3& whd)
			: m_id(id), m_asWHD(whd) {
			assert(m_id == ShapeId::FLOOR_BOX);
		}

		constexpr ModelDescription(const ShapeId id, const glm::vec3& from, const glm::vec3& to)
			: m_id(id), m_asFromTo{ from, to } {
			assert(m_id == ShapeId::QUAD || m_id == ShapeId::BOX);
		}

		constexpr ModelDescription(ModelDescription&& other) noexcept
			: m_id(other.m_id), m_asFromTo{ other.m_asFromTo[0], other.m_asFromTo[1] } { } // 'cause m_asFromTo is the largest

		Mesh generateMesh(gl::Vertices texCoords, const math::DirectionFlag VNSurroundings) const;

	private:
		gl::Vertices getTexCoordsForVNS(const gl::Vertices& texCoords, const math::DirectionFlag VNSurroundings) const;
	};
}
