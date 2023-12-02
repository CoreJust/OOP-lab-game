// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ContinuousEffect.h"

bool ContinuousEffect::update(Entity& entity, World& world, const float deltaTime) {
    if (!m_isApplied) {
        applyTo(entity, world);
        m_isApplied = true;
    }

    m_time -= deltaTime;

	if (m_time <= 0.f) {
		eraseEffect(entity, world);
		return true;
	}

    return false;
}

void ContinuousEffect::applyTo(Entity& entity, World& world) {
	switch (m_id) {
		case EffectId::ACCELERATION: entity.getStatsMut().speed *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::DECCELERATION: entity.getStatsMut().speed /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::HEALTH_INCREASE: entity.getStatsMut().maxHealth *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::HEALTH_DECREASE: entity.getStatsMut().maxHealth /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::POWER_INCREASE: entity.getStatsMut().power *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::POWER_DECREASE: entity.getStatsMut().power /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::DEFENCE_INCREASE: entity.getStatsMut().defence *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::DEFENCE_DECREASE: entity.getStatsMut().defence /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::BLINDNESS: entity.setBlind(true); break;
		case EffectId::IMMORTALITY: entity.setImmortalMode(true); break;
		case EffectId::SPIRITUAL_FORM: entity.setSpiritualMode(true); break;
		case EffectId::INVISIBILITY: entity.setInvisibleMode(true); break;
	default:
		assert(false && "Not a continuous effect");
		break;
	}
}

std::unique_ptr<Effect> ContinuousEffect::copy() {
	return std::make_unique<ContinuousEffect>(m_id, m_level, m_time);
}

std::string ContinuousEffect::toString() const {
	return Effect::toString() + " for " + std::to_string(m_time) + " seconds";
}

void ContinuousEffect::updateTime(const ContinuousEffect& other) {
	assert(m_id == other.getId());

	m_time = m_time > other.m_time ? m_time : other.m_time;
}

void ContinuousEffect::eraseEffect(Entity& entity, World& world) {
	switch (m_id) {
		case EffectId::ACCELERATION: entity.getStatsMut().speed /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::DECCELERATION: entity.getStatsMut().speed *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::HEALTH_INCREASE: entity.getStatsMut().maxHealth /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::HEALTH_DECREASE: entity.getStatsMut().maxHealth *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::POWER_INCREASE: entity.getStatsMut().power /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::POWER_DECREASE: entity.getStatsMut().power *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::DEFENCE_INCREASE: entity.getStatsMut().defence /= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::DEFENCE_DECREASE: entity.getStatsMut().defence *= 1.f + Effect::EFFECT_BASE_PER_LEVEL * m_level; break;
		case EffectId::BLINDNESS: entity.setBlind(false); break;
		case EffectId::IMMORTALITY: entity.setImmortalMode(false); break;
		case EffectId::SPIRITUAL_FORM: entity.setSpiritualMode(false); break;
		case EffectId::INVISIBILITY: entity.setInvisibleMode(false); break;
	default:
		assert(false && "Not a continuous effect");
		break;
	}
}
