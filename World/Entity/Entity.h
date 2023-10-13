// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "EntityId.h"
#include "EntityStats.h"
#include "World/WorldObject.h"
#include "World/Effects/EffectPool.h"

// Basic class for all the entities (existances with position and health, etc) in the game world
class Entity : public WorldObject {
protected:
	const EntityId m_id;
	EntityStats m_stats;
	EffectPool m_effectPool;

	float m_health = 0;
	bool m_immortalMode = false;
	bool m_invisibleMode = false;
	bool m_spiritualMode = false;

protected:
	Entity(math::Vector2f pos, EntityId id, World& pWorld);

	// Calculates the actual damage according to defence
	float calcDamage(float amount) const;

public:
	virtual ~Entity() = default;

	void move(const math::Vector2f& offset);
	void setPos(const math::Vector2f& pos);

	void heal(float amount);
	void dealDamage(float amount);
	void dealPureDamage(float amount); // Ignores defence

	void setImmortalMode(bool mode) noexcept;
	void setInvisibleMode(bool mode) noexcept;
	void setSpiritualMode(bool mode) noexcept;

	float getHealth() const noexcept;
	const EntityStats& getStats() const noexcept;
	EntityStats& getStatsMut() noexcept;
	EntityId getId() const noexcept;

	EffectPool& getEffectPoolMut() noexcept;

	bool isInImmortalMode() const noexcept;
	bool isInInvisibleMode() const noexcept;
	bool isInSpiritualMode() const noexcept;
	bool isAlive() const noexcept;

	std::string toString() const;
};