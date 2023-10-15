// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "LevelChangerTileData.h"

LevelChangerTileData::LevelChangerTileData(WorldLevelId newLevelId) : m_newLevel(newLevelId) { }

void LevelChangerTileData::update(math::Vector2f pos, World& world, Player& player, const float deltaTime) {
	
}

void LevelChangerTileData::onStep(math::Vector2f pos, World& world, Entity& entity) {
	if (entity.getId() != EntityId::PLAYER) {
		return;
	}

	entity.setPos({ 0, 0 });
	world = World(m_newLevel);
}

std::unique_ptr<TileData> LevelChangerTileData::copy() {
	return std::make_unique<LevelChangerTileData>(m_newLevel);
}
