// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "../TileData.h"
#include "World/World.h"
#include "World/Entity/Player.h"

// Teleports player to a new level
class LevelChangerTileData : public TileData {
private:
	WorldLevelId m_newLevel;

public:
	LevelChangerTileData(WorldLevelId newLevelId);

	void update(math::Vector2f pos, World& world, Player& player, const float deltaTime) override; // Does nothing
	void onStep(math::Vector2f pos, World& world, Entity& entity) override;

	std::unique_ptr<TileData> copy() override;
};