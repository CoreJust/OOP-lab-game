// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include "Effect.h"
#include "World/World.h"
#include "World/Entity/Entity.h"

/*
*	ContinuousEffect(.h/.cpp) contains class ContinuousEffect that inherits
*	parent class Effect.
*
*	Continuous effect is acquired, instantly applied, then after a period of time
*	the effect is cancelled and removed.
*/

// Implements continuous effects with single activation
// Basic class for other continuous effects
class ContinuousEffect : public Effect {
protected:
	float m_time; // Time left
	bool m_isApplied;

public:
	constexpr ContinuousEffect(const EffectId id, const float level = 1.f, const float time = 30.f) noexcept
		: Effect(id, level), m_time(time), m_isApplied(false) {
		assert(m_id.isContinuous());
	}

	bool update(Entity& entity, World& world, const float deltaTime) override;

	void updateTime(const ContinuousEffect& other); // Increases the time if the other has a higher time

	std::unique_ptr<Effect> copy() override;
	std::string toString() const override;

protected:
	virtual void eraseEffect(Entity& entity, World& world);
	void applyTo(Entity& entity, World& world) override;
};