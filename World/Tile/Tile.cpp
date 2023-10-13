// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Tile.h"
#include "TileDatas/EffectGiverTileData.h"
#include "World/Effects/InstantEffect.h"
#include "World/Effects/ContinuousEffect.h"

Tile::Tile() noexcept
	: Tile(TileId::EMPTINESS) {

}

Tile::Tile(const Tile& other) noexcept
	: m_id(other.m_id), m_tileData(other.copyTileData()) {
	m_isObstacle = m_id.getTileInfo().speedModifier == TileInfo::OBSTACLE;
}

Tile::Tile(Tile&& other) noexcept 
	: m_id(std::move(other.m_id)), m_tileData(std::move(other.m_tileData)) {
	m_isObstacle = m_id.getTileInfo().speedModifier == TileInfo::OBSTACLE;
}

Tile::Tile(TileId id, utils::Tribool isObstacle) noexcept
	: m_id(id), m_tileData(getDefaultTileDataFor(id)), m_isObstacle(isObstacle.toBool(id.getTileInfo().speedModifier == 0)) {

}

Tile::Tile(TileId id, std::unique_ptr<TileData> tileData, utils::Tribool isObstacle)
	: m_id(id), m_tileData(std::move(tileData)), m_isObstacle(isObstacle.toBool(id.getTileInfo().speedModifier == 0)) {

}

Tile& Tile::operator=(const Tile& other) noexcept {
	m_id = other.m_id;
	m_tileData = std::unique_ptr<TileData>(other.copyTileData());
	m_isObstacle = other.m_isObstacle;

	return *this;
}

Tile& Tile::operator=(Tile&& other) noexcept {
	m_id = std::move(other.m_id);
	m_tileData = std::move(other.m_tileData);
	m_isObstacle = other.m_isObstacle;

	return *this;
}

void Tile::setIsObstacle(utils::Tribool isObstacle) {
	m_isObstacle = isObstacle.toBool(m_id.getTileInfo().speedModifier == 0);
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

std::unique_ptr<TileData> Tile::copyTileData() const {
	return m_tileData ? m_tileData->copy() : nullptr;
}

bool Tile::isInteractive() const noexcept {
	return bool(m_tileData);
}

bool Tile::isObstacle() const noexcept {
	return m_isObstacle;
}

bool Tile::isVisible() const noexcept {
	return !m_id.getTileInfo().isTransparent;
}

std::unique_ptr<TileData> Tile::getDefaultTileDataFor(TileId id) const {
	switch (m_id) {
	case TileId::STONE_PORTAL: {
		std::vector<std::shared_ptr<Effect>> effects;
		effects.emplace_back(std::make_shared<InstantEffect>(EffectId::RANDOM_TELEPORTATION));
		effects.emplace_back(std::make_shared<ContinuousEffect>(EffectId::SPIRITUAL_FORM, 1.f, 6.f));

		return std::make_unique<EffectGiverTileData>(std::move(effects), 1.f);
	} default:
		break;
	}

	return std::unique_ptr<TileData>();
}
