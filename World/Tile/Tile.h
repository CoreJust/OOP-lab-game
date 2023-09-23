#pragma once
#include <memory>

#include "TileId.h"
#include "TileData.h"

// A single tile in the world
class Tile final {
private:
	TileId m_id;

	// An interface representing all the qualities of a tile
	// Empty if the tile has no data
	std::unique_ptr<TileData> m_tileData;

public:
	Tile() noexcept;
	Tile(TileId id) noexcept;
	Tile(TileId id, std::unique_ptr<TileData> tileData);

	TileId getId() const noexcept;
	TileData* getTileData() noexcept;
	TileCategory getCategory() const noexcept;

	bool isInteractive() const noexcept;
	bool isObstacle() const noexcept;
	bool isVisible() const noexcept;
};