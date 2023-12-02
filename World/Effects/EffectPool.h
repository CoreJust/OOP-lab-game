// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <list>
#include <array>
#include <memory>

#include "Effect.h"

/*
*	EffectPool(.h/.cpp) contains a class that inherits manages entity's effects.
*
*	Whenever an effect is given to an entity, it is actually pushed to the entity's
*	effect pool, that then updates all of the effects and remove them from the list
*	whenever it is required.
*/

// Handles a set of effects
class EffectPool final {
private:
	std::array<std::list<std::shared_ptr<Effect>>, EffectId::NUMBER_EFFECT_IDS> m_effects;
	Entity& m_pEntity;
	World& m_pWorld;

public:
	EffectPool(Entity& pEntity, World& pWorld) noexcept;

	EffectPool& operator=(const EffectPool& other);
	EffectPool& operator=(EffectPool&& other);

	void update(const float deltaTime);

	void pushEffect(std::shared_ptr<Effect> effect);
};