// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <list>
#include <memory>

#include "Effect.h"

// Handles a set of effects
class EffectPool final {
private:
	std::list<std::shared_ptr<Effect>> m_effects;
	Entity& m_pEntity;
	World& m_pWorld;

public:
	EffectPool(Entity& pEntity, World& pWorld) noexcept;

	void update(const float deltaTime);

	void pushEffect(std::shared_ptr<Effect> effect);
};