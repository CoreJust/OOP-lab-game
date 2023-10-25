// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <memory>
#include "EffectId.h"
#include "World/Entity/EntityId.h"

class World;
class Entity;

/*
* Basic class for effect that are being put upon an entity for some time
* For most effects the impact is multiplying the corresponding stat by 1.1 * level
* Such effects: acceleration/decceleration, health increase/health decrease, power increase/power decrease,
*				defence increase/defence decrease
* Other effects:
*		1) Instant heal/damage : heals/damages for 50 hp per level
*		2) Continuous heal/damage : heals/damages for 10 hp per level each 4 seconds
*		3) Immortality : self-obvious - you can't die, no levels
*		4) Spiritual form : allows to walk through walls, no levels
*		5) Invisibility : self-obvious - enemies wouldn't notice you (the more the higher the level up to the 10th)
*		6) Random teleportation : teleports you to a random passable place within the map
*/

class Effect {
public:
	constexpr inline static float EFFECT_BASE_PER_LEVEL = 0.1f;

	constexpr inline static float INSTANT_HEAL_PER_LEVEL = 50.f;
	constexpr inline static float INSTANT_DAMAGE_PER_LEVEL = 50.f;

	constexpr inline static float CONTINUOUS_HEAL_PER_LEVEL = 10.f;
	constexpr inline static float CONTINUOUS_DAMAGE_PER_LEVEL = 10.f;

	constexpr inline static float DEFAULT_CONTINUOUS_EFFECT_WORK_PERIOD = 4.f; // four seconds per activating

protected:
	EffectId m_id;
	float m_level; // can be non-whole

protected:
	constexpr Effect(const EffectId id, const float level = 1.f) noexcept : m_id(id), m_level(level) {
		assert(m_level > 0.1f); // Cannot be too small or negative
	}

public:
	constexpr Effect(const Effect&) noexcept = default;
	constexpr Effect(Effect&&) noexcept = default;

	virtual ~Effect() = default;

	// Returns true if the effect ended and must be cleared
	virtual bool update(Entity& entity, World& world, const float deltaTime) = 0;

	virtual std::unique_ptr<Effect> copy() = 0;
	
	inline virtual std::string toString() const {
		return m_id.toString() + " level " + std::to_string(m_level);
	}

	constexpr EffectId getId() const noexcept {
		return m_id;
	}

	constexpr float getLevel() const noexcept {
		return m_level;
	}

protected:
	virtual void applyTo(Entity& entity, World& world) = 0;
};