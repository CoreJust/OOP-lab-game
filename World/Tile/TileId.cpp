// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TileId.h"

#include <cassert>

const TileInfo& TileId::getTileInfo() const {
	static TileInfo s_tileIdInfos[] {
		/*		 TileCategory				Hardness					Speed modifier		Is visible */
		TileInfo(TileCategory::EMPTINESS,	TileInfo::INDESTRUCTIBLE,	1,					TileInfo::TRANSPARENT), // emptiness

		TileInfo(TileCategory::FLOOR,		0,							1,					TileInfo::VISIBLE),		// stone floor

		TileInfo(TileCategory::WALL,		0,							TileInfo::OBSTACLE, TileInfo::VISIBLE),		// stone wall

		TileInfo(TileCategory::FLOOR_OBJECT, 0,							TileInfo::OBSTACLE, TileInfo::VISIBLE),		// stone

		TileInfo(TileCategory::FLOOR,		TileInfo::INDESTRUCTIBLE,	0.25,				TileInfo::VISIBLE),		// stone portal
	};

	assert(m_id < std::size(s_tileIdInfos));

	return s_tileIdInfos[m_id];
}

TextureId TileId::getTileTexture() const {
	return TextureId(static_cast<TextureId::Value>(m_id));
}

std::string TileId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_tileIdNames[] {
		"EMPTINESS",

		"STONE_FLOOR",

		"STONE_WALL",

		"STONE",

		"STONE_PORTAL",

		"NUMBER_TILE_IDS"
	};

	assert(m_id < std::size(s_tileIdNames));

	return s_tileIdNames[m_id];
}