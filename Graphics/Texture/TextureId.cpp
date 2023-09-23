#include "TextureId.h"

#include <cassert>

std::string TextureId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_textureIdNames[] {
		"NO_TEXTURE",

		// Tiles
		"STONE_FLOOR",
		"STONE_WALL",
		"STONE",

		"NUMBER_TEXTURE_IDS"
	};

	assert(m_id < std::size(s_textureIdNames));

	return s_textureIdNames[m_id];
}

std::string TextureId::getResourceLocation() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_textureIdLocs[] {
		"",

		"stone_floor",
		"stone_wall",
		"stone"

		""
	};

	assert(m_id < std::size(s_textureIdLocs) && m_id != NUMBER_TEXTURE_IDS);

	return s_textureIdLocs[m_id];
}
