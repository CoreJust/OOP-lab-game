// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Enemy.h"

/*
*	LostInMaze(.h/.cpp) contains a class that implements one of the
*	enemy templates - an adventurer that got lost in maze and was corroded.
*
*	Lost in maze wanders in the maze and is highly aggressive to the player.
*/

class LostInMaze final : public Enemy<
	EnemyMovePolicy::STRAIGHT_ROAMING,
	EnemyAttackPolicy::PROACTIVE_PURSUIT,
	EnemyPlayerInteractionPolicy::NORMAL_HIT
> {
public:
	LostInMaze(const math::Vector2f& pos, World& pWorld);
};
