// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "World/World.h"

/*
*	EnemyGenerator(.h/.cpp) contains a class that adds enemies to the world.
*/

class EnemyGenerator final {
private:
	World& m_pWorld;
	std::vector<std::pair<EntityId, uint32_t>> m_entities;
	float m_minDistance;

public:
	EnemyGenerator(World& pWorld, std::vector<std::pair<EntityId, uint32_t>> entities, const float minDistance = 6.f);

	void generate();
};