// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ShapeId.h"

std::string_view model::ShapeId::toString() const {
	static std::string s_tileShapeIdNames[] {
		"EMPTINESS",

		"QUAD",
		"BOX",

		"FLAT_FLOOR",
		"FLAT_FLOOR_OBJECT",
		"SIMPLE_WALL",

		"FLOOR_BOX",

		"NUMBER_TILE_SHAPE_IDS"
	};

	assert(m_value < std::size(s_tileShapeIdNames));

	return s_tileShapeIdNames[m_value];
}
