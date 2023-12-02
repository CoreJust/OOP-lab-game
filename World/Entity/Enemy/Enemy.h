// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "EnemyBase.h"

/*
*	Enemy.h contains a class that implements an enemy.
*/

template<
	EnemyMovePolicy::Value MovePolicy, 
	EnemyAttackPolicy::Value AttackPolicy, 
	EnemyPlayerInteractionPolicy::Value InteractionPolicy
>
class Enemy : public EnemyBase {
protected:
	Enemy(
		const float attackRange,
		const float sightRange,
		const float pursuitRange,
		const EntityId id,
		const math::Vector2f& pos,
		World& pWorld
	) noexcept :
		EnemyBase(
			EnemyBehaviour(MovePolicy, AttackPolicy, InteractionPolicy, attackRange, sightRange, pursuitRange),
			id,
			pos,
			pWorld
		) { }
};
