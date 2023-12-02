// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Enemy.h"

/*
*	VenomousPlant(.h/.cpp) contains a class that implements one of the
*	enemy templates - a venomous plant.
*
*	A venomous plant is an entity that doesn't move and simply attacks player
*	whenever they get close enough.
*/

class VenomousPlant final : public Enemy<
	EnemyMovePolicy::NO_MOVING,
	EnemyAttackPolicy::IGNORE,
	EnemyPlayerInteractionPolicy::POISONING
> {
public:
	VenomousPlant(const math::Vector2f& pos, World& pWorld);
};
