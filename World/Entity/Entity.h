// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "EntityId.h"
#include "EntityStats.h"
#include "World/WorldObject.h"
#include "World/Effects/EffectPool.h"

/*
*	Entity(.h/.cpp) contains a base class for all the Entities.
*
*	It inherits the WorldObject, since an Entity is always present in the world
*	and has some changeable position.
* 
*	The Entity class contains entities characteristics - EntityStats - and its
*	Effects - via EffectPool.
* 
*	It manages the entities characteristics, but the class works passively -
*	it doesn't act on its own and just accepts outer calls (like putting effects,
*	damaging/healing it, or moving around). The actual logic of Entities behaviour
*	is handled in the *Controller class.
* 
*	There are Entity's inheritors that differ in their data and/or methods.
*/

// Basic class for all the entities (existances with position and health, etc) in the game world
class Entity : public WorldObject {
protected:
	EntityId m_id;
	EntityStats m_stats;
	EffectPool m_effectPool;

	float m_health = 0;
	bool m_immortalMode = false;
	bool m_invisibleMode = false;
	bool m_spiritualMode = false;
	bool m_isBlind = false;

protected:
	Entity(const math::Vector2f& pos, const float rot, const EntityId id, World& pWorld);
	Entity(const math::Vector2f& pos, const EntityId id, World& pWorld);

	Entity& operator=(const Entity& other);
	Entity& operator=(Entity&& other) noexcept;

	// Calculates the actual damage according to defence
	float calcDamage(float amount) const;

public:
	virtual ~Entity() = default;

	void move(const math::Vector2f& offset);
	void setPos(const math::Vector2f& pos);

	void rotate(const float angle);
	void setRotation(const float angle);

	void heal(const float amount);
	void dealDamage(const float amount);
	void dealPureDamage(const float amount); // Ignores defence

	void setImmortalMode(const bool mode) noexcept;
	void setInvisibleMode(const bool mode) noexcept;
	void setSpiritualMode(const bool mode) noexcept;
	void setBlind(const bool value) noexcept;

	float getHealth() const noexcept;
	const EntityStats& getStats() const noexcept;
	EntityStats& getStatsMut() noexcept;
	EntityId getId() const noexcept;

	EffectPool& getEffectPoolMut() noexcept;

	bool isInImmortalMode() const noexcept;
	bool isInInvisibleMode() const noexcept;
	bool isInSpiritualMode() const noexcept;
	bool isBlind() const noexcept;
	bool isAlive() const noexcept;

	std::string toString() const;
};