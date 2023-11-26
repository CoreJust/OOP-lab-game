// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TileId.h"
#include "Graphics/Model/ModelDescription.h"

#include <cassert>

const TileInfo& TileId::getTileInfo() const {
	static TileInfo s_tileIdInfos[] {
		/*		 TileCategory				Hardness					Speed modifier		Is visible */
		TileInfo(TileCategory::EMPTINESS,	TileInfo::INDESTRUCTIBLE,	1,					TileInfo::TRANSPARENT), // emptiness

		TileInfo(TileCategory::FLOOR,		0,							1,					TileInfo::VISIBLE),		// stone floor

		TileInfo(TileCategory::WALL,		0,							TileInfo::OBSTACLE, TileInfo::VISIBLE),		// stone wall

		TileInfo(TileCategory::FLOOR_OBJECT, 0,							TileInfo::OBSTACLE, TileInfo::VISIBLE),		// stone

		TileInfo(TileCategory::FLOOR,		TileInfo::INDESTRUCTIBLE,	0.25,				TileInfo::VISIBLE),		// stone portal
		TileInfo(TileCategory::FLOOR_OBJECT,TileInfo::INDESTRUCTIBLE,	0.1,				TileInfo::VISIBLE),		// next level portal
		TileInfo(TileCategory::FLOOR_OBJECT,TileInfo::INDESTRUCTIBLE,	0.6,				TileInfo::VISIBLE),		// saint spring
		TileInfo(TileCategory::FLOOR_OBJECT,TileInfo::INDESTRUCTIBLE,	1.2,				TileInfo::VISIBLE),		// poison cloud
	};

	assert(m_value < std::size(s_tileIdInfos));

	return s_tileIdInfos[m_value];
}

const model::ModelDescription& TileId::getModelDescription() const {
	static model::ModelDescription s_tileIdModels[] {
		// emptiness
		model::ModelDescription(model::ShapeId::EMPTINESS),

		// stone floor
		model::ModelDescription(model::ShapeId::FLAT_FLOOR),

		// stone wall
		model::ModelDescription(model::ShapeId::SIMPLE_WALL, math::DirectionFlag::ALL_DIRECTIONS),

		// stone
		model::ModelDescription(model::ShapeId::FLOOR_BOX, /* WHD (sizes) =  */{ 0.75, 0.375, 0.75 }),

		// stone portal
		model::ModelDescription(model::ShapeId::FLAT_FLOOR),

		// next level portal
		model::ModelDescription(model::ShapeId::FLOOR_BOX, /* WHD (sizes) =  */{ 0.75, 0.375, 0.75 }),

		// saint spring
		model::ModelDescription(model::ShapeId::FLAT_FLOOR_OBJECT),

		// poison cloud
		model::ModelDescription(model::ShapeId::FLOOR_BOX, /* WHD (sizes) =  */{ 1, 1, 1 })
	};

	assert(m_value < std::size(s_tileIdModels));

	return s_tileIdModels[m_value];
}

model::TextureCoords& TileId::loadToTexCoords(model::TextureCoords& texCoords) const {
	switch (m_value) {
		case EMPTINESS: break;
		case STONE_FLOOR: texCoords.addTextureRect(math::Rectf(0, 0, 1, 1)); break;
		case STONE_WALL: texCoords.addTextureRect(math::Rectf(0, 1, 1, 3)).repeat(4); break;
		case STONE: texCoords.addTextureBox(math::Vector2f(0.25f, 2.25f), 0.75f, 0.375f, 0.75f); break;
		case STONE_PORTAL: texCoords.addTextureRect(math::Rectf(1, 0, 2, 1)); break;
		case NEXT_LEVEL_PORTAL: texCoords.addTextureBox(math::Vector2f(0.25f, 3.375f), 0.75f, 0.375f, 0.75f); break;
		case SAINT_SPRINGS: texCoords.addTextureRect(math::Rectf(0.25f, 3.375f, 1.f, 4.125f)); break;
		case POISON_CLOUD: texCoords.addTextureRect(math::Rectf(2, 0, 3, 1)).repeat(6); break;
	default: assert(false && "Unknown tile ID"); break;
	}

	return texCoords;
}

TileCategory TileId::getCategory() const {
	return getTileInfo().category;
}

bool TileId::isBackground() const {
	TileCategory cat = getCategory();
	return cat == TileCategory::EMPTINESS || cat == TileCategory::FLOOR || cat == TileCategory::WALL;
}

bool TileId::isForeground() const {
	TileCategory cat = getCategory();
	return cat == TileCategory::EMPTINESS || cat == TileCategory::FLOOR_OBJECT || cat == TileCategory::WALL_OBJECT;
}

std::string_view TileId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_tileIdNames[] {
		"EMPTINESS",

		"STONE_FLOOR",

		"STONE_WALL",

		"STONE",

		"STONE_PORTAL",
		"NEXT_LEVEL_PORTAL",
		"SAINT_SPRING",
		"POISON_CLOUD",

		"NUMBER_TILE_IDS"
	};

	assert(m_value < std::size(s_tileIdNames));

	return s_tileIdNames[m_value];
}