// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "World.h"
#include "Entity/Player.h"

/*
*	LevelLoader(.h/.cpp) contains a class that manages the loading of a new level
*	and (in the future) loading out the previous level if there is.
*/

class LevelLoader final {
private:
	World& m_world;
	Player& m_player;
	bool m_resetPlayer;

public:
	constexpr LevelLoader(World& world, Player& player, bool resetPlayer = false) noexcept
		: m_world(world), m_player(player), m_resetPlayer(resetPlayer) { }

	void loadLevel(const WorldLevelId id);
	void loadNextLevel();
	void saveLevel();
};