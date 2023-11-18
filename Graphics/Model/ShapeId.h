// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"

/*
*	ShapeId(.h/.cpp) contains a class that enumerates the template shapes of models.
* 
*	For each shape there is a set of characteristics.
*/

namespace model {
	class ShapeId final : public BasicId {
	public:
		enum Value : id_t {
			EMPTINESS = 0, // No shape
			
			// shape used in other shapes - a single quad
			// The coordinates of the vertices must be the same for one of the coords axes
			// Parameters: a vertex and the opposite one
			QUAD, // [vec3, vec3]

			// shape used in other shapes - a simple box
			// Parameters: a vertex and the opposite one
			BOX, // [vec3, vec3]

			FLAT_FLOOR, // the simplest shape - a square on the floor
			FLAT_FLOOR_OBJECT, // Same as the FLAT_FLOOR, but is rendered over it

			// the basic shape of a wall - 4 rects, one on each side
			// Parameters: whether the sides are active (since adjacent walls are obviously
			// not rendered
			SIMPLE_WALL, // [bool, bool, bool, bool]

			// A box on the floor, a more complex shape
			// Parameters: the height, widht and depths
			FLOOR_BOX, // [float, float, float]

			NUMBER_TILE_SHAPE_IDS
		};

	public:
		constexpr ShapeId() = delete;
		constexpr ShapeId(Value value) noexcept : BasicId(value) {
			assert(value < NUMBER_TILE_SHAPE_IDS);
		}

		constexpr ShapeId& operator=(ShapeId other) noexcept {
			m_id = id_t(other);

			return *this;
		}

		constexpr explicit operator Value() const noexcept {
			return static_cast<Value>(m_id);
		}

		std::string toString() const override;
	};
}
