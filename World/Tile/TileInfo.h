// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>

/*
*	TileInfo.h contains two corelated types:
*		1) TileCategory - all tiles in the game are split with two aspects:
*			Whether they belong to the passable (abstactly) type - floor,
*				or to the obstacle type - wall
*			And whether they are in the background or in the foreground.
*			Also, there is a separate category of emptiness that belongs
*			to neither one.
* 
*		2) TileInfo - represent the general information on a certain kind of tile
*			(the tile ID). It includes the category and also:
*			1. Hardness - the ability of the tile to withstand damage (not used as of now).
*			2. Speed modifier - some tiles can accelerate entities during their movement
*				over the tiles, and some can do the opposite. Also, the modifier may be
*				zero, thus making the tile impassable. That's how the obstacles are marked.
*			3. Transparantness - some tiles might be opaque and some - transparent. That's it.
*/

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
	const TileCategory category;
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