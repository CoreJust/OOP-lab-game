// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "World/Entity/Player.h"
#include "World/Entity/Behaviour/EnemyBehaviour.h"

/*
*	EnemyBase(.h/.cpp) contains a base class for all the enemies.
*/

class EnemyBase : public Entity {
protected:
	EnemyBehaviour m_behaviour;

protected:
	EnemyBase(
		EnemyBehaviour behaviour,
		const EntityId id,
		const math::Vector2f& pos,
		World& pWorld
	) noexcept;

public:
	virtual void onAttack(World& world, Player& player);

	constexpr EnemyBehaviour& getBehaviour() noexcept {
		return m_behaviour;
	}
};
