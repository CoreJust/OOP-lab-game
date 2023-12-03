// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PeriodicalEffect.h"

bool PeriodicalEffect::update(Entity& entity, World& world, const float deltaTime) {
    if (m_currentPeriod >= 0.f) {
        applyTo(entity, world);
        m_currentPeriod -= m_period;
    }

    m_time -= deltaTime;
    m_currentPeriod += deltaTime;

    if (m_time <= 0.f) {
        eraseEffect(entity, world);
        return true;
    }

    return false;
}

std::unique_ptr<Effect> PeriodicalEffect::copy() {
    return std::make_unique<PeriodicalEffect>(m_id, m_level, m_time, m_period);
}

std::string PeriodicalEffect::toString() const {
    return ContinuousEffect::toString() + " with period of " + std::to_string(m_period) + " seconds";
}

void PeriodicalEffect::eraseEffect(Entity& entity, World& world) {
    return; // Nothing here
}

void PeriodicalEffect::applyTo(Entity& entity, World& world) {
	switch (m_id) {
    case EffectId::CONTINUOUS_DAMAGE:
        if (entity.getId() == EntityId::PLAYER) {
            (*(Player*)&entity).dealDamageToPlayer(Effect::CONTINUOUS_DAMAGE_PER_LEVEL * m_level, m_id);
        } else {
            entity.dealDamage(Effect::CONTINUOUS_DAMAGE_PER_LEVEL * m_level);
        }
        break;
	case EffectId::CONTINUOUS_HEALING: entity.heal(Effect::CONTINUOUS_HEAL_PER_LEVEL * m_level); break;
	default:
		assert(false && "Not a periodical effect");
		break;
	}
}
