// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "EnemyController.h"

/*
*	EnemySpawner(.h/.cpp) contains a class that provides 
*	a convenient for spawning an enemy.
*/

class EnemySpawner final {
private:
	World& m_pWorld;

public:
	EnemySpawner(World& pWorld) noexcept;

	std::unique_ptr<EnemyController> spawn(const EntityId id, const math::Vector2f& pos);
};