// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Entity.h"

#include <cassert>
#include <algorithm> // for std::min/max
#include <format>

Entity::Entity(math::Vector2f pos, EntityId id, World& pWorld)
	: WorldObject(std::move(pos)),
	m_id(id),
	m_stats(id.getEntityStats()),
	m_health(id.getEntityStats().maxHealth),
	m_effectPool(*this, pWorld) 
{

}

// Preliminary implementation
// TODO: Review defence system
float Entity::calcDamage(float amount) const {
	// Progressive scale for damage reduction with defence
	// Factors for defence calculation:
	// 10% gives 100% damage reduction, next 15% - 90%, 35% - 75%, and final 40% - 40%
	const static float DEFENCE_POWERS_FACTORS[4] = { 0.1f * 1, 0.15f * 0.9f, 0.35f * 0.75f, 0.4f * 0.4f };

	if (m_stats.defence <= 0) {
		return amount;
	}

	float result = 0;
	for (size_t i = 0; i < 4; i++) {
		float defencePower = m_stats.defence * DEFENCE_POWERS_FACTORS[i];

		if (defencePower > amount) {
			return result;
		}

		result += amount - defencePower;
		amount -= defencePower;
	}

	return result;
}

void Entity::move(const math::Vector2f& offset) {
	m_pos += offset;
}

void Entity::setPos(const math::Vector2f& pos) {
	m_pos = pos;
}

void Entity::heal(float amount) {
	assert(amount >= 0); // Healing can be negative, but must be processed as damage in the higher-level logic

	m_health = std::min(m_health + amount, m_stats.maxHealth);
}

void Entity::dealDamage(float amount) {
	assert(amount >= 0); // Damage can be negative, but must be processed as healing in the higher-level logic

	if (m_immortalMode) {
		return;
	}

	m_health = std::max(m_health - calcDamage(amount), 0.f);
}

void Entity::dealPureDamage(float amount) {
	assert(amount >= 0); // Damage can be negative, but must be processed as healing in the higher-level logic

	if (m_immortalMode) {
		return;
	}

	m_health = std::max(m_health - amount, 0.f);
}

void Entity::setImmortalMode(bool mode) noexcept {
	m_immortalMode = mode;
}

void Entity::setInvisibleMode(bool mode) noexcept {
	m_invisibleMode = mode;
}

void Entity::setSpiritualMode(bool mode) noexcept {
	m_spiritualMode = mode;
}

float Entity::getHealth() const noexcept {
	return m_health;
}

const EntityStats& Entity::getStats() const noexcept {
	return m_stats;
}

EntityStats& Entity::getStatsMut() noexcept {
	return m_stats;
}

EntityId Entity::getId() const noexcept {
	return m_id;
}

EffectPool& Entity::getEffectPoolMut() noexcept {
	return m_effectPool;
}

bool Entity::isInImmortalMode() const noexcept {
	return m_immortalMode;
}

bool Entity::isInInvisibleMode() const noexcept {
	return m_invisibleMode;
}

bool Entity::isInSpiritualMode() const noexcept {
	return m_spiritualMode;
}

bool Entity::isAlive() const noexcept {
	return m_health > 0;
}

std::string Entity::toString() const {
	return std::format("[entity {0} at {1}]", m_id.toString(), m_pos.toString());
}
