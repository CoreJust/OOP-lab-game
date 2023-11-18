#include "ShapeId.h"

std::string model::ShapeId::toString() const {
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

	assert(m_id < std::size(s_tileShapeIdNames));

	return s_tileShapeIdNames[m_id];
}
