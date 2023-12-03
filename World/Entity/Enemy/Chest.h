// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Enemy.h"

/*
*	Chest(.h/.cpp) contains a class that implements one of the
*	enemy templates - a chest.
*
*	A chest increases player's stats permanently.
*/

class Chest final : public Enemy<
	EnemyMovePolicy::NO_MOVING,
	EnemyAttackPolicy::IGNORE,
	EnemyPlayerInteractionPolicy::NORMAL_HIT
> {
public:
	Chest(const math::Vector2f& pos, World& pWorld);

	void onAttack(World& world, Player& player) override;
};
