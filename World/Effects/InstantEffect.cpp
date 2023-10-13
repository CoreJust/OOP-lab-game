// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "InstantEffect.h"

bool InstantEffect::update(Entity& entity, World& world, const float deltaTime) {
    applyTo(entity, world);

    return true; // It is applied once and then finished
}

std::unique_ptr<Effect> InstantEffect::copy() {
	return std::make_unique<InstantEffect>(m_id, m_level);
}

void InstantEffect::applyTo(Entity& entity, World& world) {
	switch (m_id) {
		case EffectId::HEAL: entity.heal(Effect::INSTANT_HEAL_PER_LEVEL * m_level); break;
		case EffectId::DAMAGE: entity.dealDamage(Effect::INSTANT_DAMAGE_PER_LEVEL * m_level); break;
		case EffectId::RANDOM_TELEPORTATION: entity.setPos(world.getRandomPassableLocation().to<float>() + 0.5f); break;
	default:
		assert(false && "Not an instant effect");
		break;
	}
}
