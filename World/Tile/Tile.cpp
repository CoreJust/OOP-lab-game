#include "Tile.h"

Tile::Tile() noexcept
	: Tile(TileId::EMPTINESS) {

}

Tile::Tile(TileId id) noexcept
	: m_id(id) {

}

Tile::Tile(TileId id, std::unique_ptr<TileData> tileData)
	: m_id(id), m_tileData(std::move(tileData)) {

}

TileId Tile::getId() const noexcept {
	return m_id;
}

TileData* Tile::getTileData() noexcept {
	return m_tileData.get();
}

TileCategory Tile::getCategory() const noexcept {
	return m_id.getTileInfo().category;
}

bool Tile::isInteractive() const noexcept {
	return bool(m_tileData);
}

bool Tile::isObstacle() const noexcept {
	return m_id.getTileInfo().speedModifier == 0;
}

bool Tile::isVisible() const noexcept {
	return !m_id.getTileInfo().isTransparent;
}
