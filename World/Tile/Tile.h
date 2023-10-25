// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <memory>

#include "Utils/Tribool.h"
#include "TileId.h"
#include "TileData.h"

/*
*	Tile(.h/.cpp) contains a class that represents a tile in the world.
*
*	A tile is the most basic building block (a brick) of the game world.
*	The whole field is split into a square net with each cell of it being
*	filled with a tile (actually, with two tiles - the background and the foreground).
* 
*	All the tiles collectively are the game world itself, that is then filled with
*	diverse entities, player included.
* 
*	A tile has three characteristics, the most basic of which is its ID.
*	Also, there are a TileData (and both are explained in detail in the corresponding files)
*	and the boolean value of the tile being an obstacle? which is set by its ID, but can later
*	be modified (not a necessary feature, but so the requirements demanded, so what can I do?).
*/

// A single tile in the world
class Tile final {
private:
	TileId m_id;
	bool m_isObstacle;

	// An interface representing all the qualities of a tile
	// Empty if the tile has no data
	std::unique_ptr<TileData> m_tileData;

public:
	Tile() noexcept;
	Tile(const Tile& other) noexcept;
	Tile(Tile&& other) noexcept;
	Tile(TileId id, utils::Tribool isObstacle = utils::Tribool::None) noexcept; // Uses the corresponding TileData if there is for such TileId
	Tile(TileId id, std::unique_ptr<TileData> tileData, utils::Tribool isObstacle = utils::Tribool::None);

	Tile& operator=(const Tile& other) noexcept;
	Tile& operator=(Tile&& other) noexcept;

	// None for default value, according to Id
	void setIsObstacle(utils::Tribool isObstacle = utils::Tribool::None);

	TileId getId() const noexcept;
	TileData* getTileData() noexcept; // Can be nullptr
	TileCategory getCategory() const noexcept;

	std::unique_ptr<TileData> copyTileData() const;

	bool isInteractive() const noexcept;
	bool isObstacle() const noexcept;
	bool isVisible() const noexcept;

private:
	std::unique_ptr<TileData> getDefaultTileDataFor(TileId id) const;
};