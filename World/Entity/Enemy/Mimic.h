// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Enemy.h"

/*
*	Mimic(.h/.cpp) contains a class that implements one of the
*	enemy templates - a mimic.
*
*	A Mimic looks like a chest, but explodes instead of buffing.
*/

class Mimic final : public Enemy<
	EnemyMovePolicy::NO_MOVING,
	EnemyAttackPolicy::PASSIVE_PURSUIT,
	EnemyPlayerInteractionPolicy::SELF_DESTRUCT
> {
public:
	Mimic(const math::Vector2f& pos, World& pWorld);
};
