#pragma once
#include "EntityId.h"
#include "EntityStats.h"
#include "World/WorldObject.h"
#include "Graphics/Texture/Animation.h"

// Basic class for all the entities (existances with position and health, etc) in the game world
class Entity : public WorldObject {
protected:
	EntityId m_id;
	EntityStats m_stats;

	float m_health = 0;

protected:
	Entity(utils::Vector2f pos, EntityId id);

	// Calculates the actual damage according to defence
	float calcDamage(float amount) const;

public:
	void move(const utils::Vector2f& offset);
	void setPos(const utils::Vector2f& pos);

	void heal(float amount);
	void dealDamage(float amount);

	float getHealth() const;
	const EntityStats& getStats() const;

	bool isAlive() const;
};