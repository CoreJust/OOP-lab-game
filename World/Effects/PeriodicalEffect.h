// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "ContinuousEffect.h"

// Activates once in a while for some time
class PeriodicalEffect : public ContinuousEffect {
protected:
	float m_period;
	float m_currentPeriod;

public:
	constexpr PeriodicalEffect(const EffectId id, const float level = 1.f, const float time = 30.f, const float period = Effect::DEFAULT_CONTINUOUS_EFFECT_WORK_PERIOD) noexcept
		: ContinuousEffect(id, level, time), m_period(period), m_currentPeriod(0.f) {
		assert(m_id.isPeriodic());
	}

	bool update(Entity& entity, World& world, const float deltaTime) override;

	std::unique_ptr<Effect> copy() override;
	std::string toString() const override;

protected:
	virtual void eraseEffect(Entity& entity, World& world);
	void applyTo(Entity& entity, World& world) override;
};