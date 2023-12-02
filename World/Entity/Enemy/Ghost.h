// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Enemy.h"

/*
*	Ghost(.h/.cpp) contains a class that implements one of the
*	enemy templates - a ghost.
* 
*	A ghost can go through any obstacles and shocks the player upon attack.
*/

class Ghost final : public Enemy<
	EnemyMovePolicy::CLOSING_ON_PLAYER, 
	EnemyAttackPolicy::INERTIAL_PURSUIT, 
	EnemyPlayerInteractionPolicy::SHOCKING
> {
public:
	Ghost(const math::Vector2f& pos, World& pWorld);
};
