// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Vector.h"
#include "EnemyMovePolicy.h"
#include "EnemyAttackPolicy.h"
#include "EnemyPlayerInteractionPolicy.h"

/*
*	EnemyBehaviour(.h/.cpp) contains a class that allows to define
*	the behaviour of a certain enemy (or, possibly, an entity in general).
*/

class World;

class EnemyBehaviour {
private:
	EnemyMovePolicy m_movePolicy;
	EnemyAttackPolicy m_attackPolicy;
	EnemyPlayerInteractionPolicy m_interactionPolicy;

	float m_attackRange;
	float m_sightRange;
	float m_pursuitRange;

	math::Vector2f m_lastPlayerPosInSight;
	bool m_isPursuing = false;

public:
	constexpr EnemyBehaviour(
		const EnemyMovePolicy movePolicy,
		const EnemyAttackPolicy attackPolicy,
		const EnemyPlayerInteractionPolicy interactionPolicy,
		const float attackRange,
		const float sightRange,
		const float pursuitRange
	) noexcept :
		m_movePolicy(movePolicy),
		m_attackPolicy(attackPolicy),
		m_interactionPolicy(interactionPolicy),
		m_attackRange(attackRange),
		m_sightRange(sightRange),
		m_pursuitRange(pursuitRange) {
		assert(attackRange <= sightRange || sightRange == 0.f);
		assert(sightRange <= pursuitRange || pursuitRange == 0.f);

		if (m_sightRange == 0.f) {
			m_sightRange = 1e10;
		} if (m_pursuitRange == 0.f) {
			m_pursuitRange = 1e10;
		}
	}

	bool isPlayerInAttackRange(const math::Vector2f& pos, const math::Vector2f& playerPos) const;
	math::Vector2f getAttractionPoint(
		const World& world, 
		const math::Vector2f& pos, 
		const math::Vector2f& playerPos,
		const math::Vector2f& currentAttractionPoint
	);
	
	constexpr EnemyPlayerInteractionPolicy getInteractionPolicy() const noexcept {
		return m_interactionPolicy;
	}

private:
	bool isPlayerInSight(const World& world, const math::Vector2f& pos, const math::Vector2f& playerPos) const;

	math::Vector2f getAttackAttractionPoint(const World& world, const math::Vector2f& pos, const math::Vector2f& playerPos) const;
	math::Vector2f getMoveAttractionPoint(const World& world, const math::Vector2f& pos, const math::Vector2f& playerPos) const;

	// Builds the path towards the player and returns the next attraction point on the path
	math::Vector2f getAttractionOnPathToPlayer(const World& world, const math::Vector2f& pos, const math::Vector2f& playerPos) const;
};