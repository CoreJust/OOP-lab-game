// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Enemy.h"

/*
*	EvilSpirit(.h/.cpp) contains a class that implements one of the
*	enemy templates - an evil spirit.
*
*	An evil spirit usually doesn't move, has little agression range,
*	but can go through walls. Upon attack, it converts all of its HP
*	into damage and thus destroys itself. It blinds the player.
*/

class EvilSpirit final : public Enemy<
	EnemyMovePolicy::NO_MOVING,
	EnemyAttackPolicy::PASSIVE_PURSUIT,
	EnemyPlayerInteractionPolicy::NORMAL_HIT // Actully it is overloaded
> {
public:
	EvilSpirit(const math::Vector2f& pos, World& pWorld);

	void onAttack(World& world, Player& player) override;
};
