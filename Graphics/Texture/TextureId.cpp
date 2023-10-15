// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

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
		"STONE_PORTAL",
		"NEXT_LEVEL_PORTAL",
		"SAINT_SPRING",
		"POISON_CLOUD",

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
		"stone",
		"stone_portal",
		"next_level_portal",
		"saint_springs",
		"poison_cloud",

		""
	};

	assert(m_id < std::size(s_textureIdLocs) && m_id != NUMBER_TEXTURE_IDS);

	return s_textureIdLocs[m_id];
}
