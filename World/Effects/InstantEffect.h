// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include "Effect.h"
#include "World/World.h"
#include "World/Entity/Entity.h"

/*
*	InstantEffect(.h/.cpp) contains class InstantEffect that inherits
*	parent class Effect.
*
*	Instant effect is acquired, instantly applied and removed - it doesn't
*	remain on the entity.
*/

// Implements the instant effects
class InstantEffect : public Effect {
public:
	constexpr InstantEffect(const EffectId id, const float level = 1.f) noexcept : Effect(id, level) {
		assert(m_id.isInstant());
	}

	bool update(Entity& entity, World& world, const float deltaTime) override;
	std::unique_ptr<Effect> copy() override;

protected:
	void applyTo(Entity& entity, World& world) override;
};