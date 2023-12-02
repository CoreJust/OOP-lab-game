// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "../TileData.h"
#include "World/World.h"
#include "World/Entity/Player.h"

/*
*	LevelChangerTileData(.h/.cpp) contains a class that represents one of the possible TileDatas.
* 
*	The LevelChangerTileData can do single but fairly crucial things - change the game level.
*	The use of this TileData is the only way to change the level (thus advancing in the passage
*	of the game).
*
*	After being invoked it just restarts the field with a new ID (and thus the settings).
*/

// Teleports player to a new level
class LevelChangerTileData : public TileData {
public:
	LevelChangerTileData();

	void update(math::Vector2f pos, World& world, Player& player, const float deltaTime) override; // Does nothing
	void onStep(math::Vector2f pos, World& world, Entity& entity) override;

	std::unique_ptr<TileData> copy() override;
};