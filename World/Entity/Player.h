// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Entity.h"

/*
*	Player(.h/.cpp) contains a class that represents the player.
*
*	It inherits the Entity class, and just as its parent it do not
*	contain much logic on its own (or rather it mostly relies on its parent
*	and on the PlayerController, thus being simple in its implementation).
*/

class World;

class Player final : public Entity {
public:
	Player(const math::Vector2f& pos, const float rot, World& pWorld);
	Player(World& pWorld);

	void dealDamageToPlayer(const float damage, const EntityId attacker);
	void dealDamageToPlayer(const float damage, const EffectId attacker);

	math::Vector2f getViewPos() const;
};