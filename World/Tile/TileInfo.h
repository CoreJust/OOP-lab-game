#pragma once
#include <cassert>

enum class TileCategory : uint8_t {
	EMPTINESS = 0,

	FLOOR,
	WALL,

	FLOOR_OBJECT, // can be put on floor
	WALL_OBJECT, // can be put on wall

	NUMBER_TILE_CATEGORIES
};

// Similar to EntityStats, but for Tiles
// Unlike EntityStats, it is not expected to be contained in Tile
//   since it is not mutable - for any TileId TileInfo is always the same
struct TileInfo {
	const float hardness;
	const float speedModifier; // acceleration or deceleration on tiles of the kind
	TileCategory category;
	const bool isTransparent;

	constexpr TileInfo(TileCategory category, float hardness, float speedModifier, bool isTransparent)
		: hardness(hardness), speedModifier(speedModifier), category(category), isTransparent(isTransparent) {
		assert(category != TileCategory::WALL || speedModifier == 0); // walls are always obstacles
	}

	///  Some constants for better code comprehension  ///

	constexpr static float INDESTRUCTIBLE = -1.f;
	constexpr static float OBSTACLE = 0.f;
	constexpr static bool TRANSPARENT = true;
	constexpr static bool VISIBLE = false;
};