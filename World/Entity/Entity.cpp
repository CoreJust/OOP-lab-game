#include "Entity.h"

#include <algorithm>

Entity::Entity(utils::Vector2f pos, EntityId id)
	: WorldObject(std::move(pos)),
	m_id(id),
	m_stats(id.getEntityStats()),
	m_health(id.getEntityStats().maxHealth) {

}

float Entity::calcDamage(float amount) const {
	const static float DEFENCE_POWERS_K[4] = { 0.1f * 1, 0.15f * 0.9f, 0.35f * 0.75f, 0.4f * 0.4f };

	if (m_stats.defence <= 0) {
		return amount;
	}

	float result = 0;
	for (size_t i = 0; i < 4; i++) {
		float defencePower = m_stats.defence * DEFENCE_POWERS_K[i];

		if (defencePower > amount) {
			return result;
		}

		result += amount - defencePower;
		amount -= defencePower;
	}

	return result;
}

void Entity::move(const utils::Vector2f& offset) {
	m_pos += offset;
}

void Entity::setPos(const utils::Vector2f& pos) {
	m_pos = pos;
}

void Entity::heal(float amount) {
	m_health = std::clamp(m_health + amount, 0.f, m_stats.maxHealth);
}

void Entity::dealDamage(float amount) {
	m_health = std::clamp(m_health - calcDamage(amount), 0.f, m_stats.maxHealth);
}

float Entity::getHealth() const {
	return m_health;
}

const EntityStats& Entity::getStats() const {
	return m_stats;
}

bool Entity::isAlive() const {
	return m_health > 0;
}
