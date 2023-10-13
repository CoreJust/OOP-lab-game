// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"

class EffectId : public BasicId {
public:
	enum Value : id_t {
		// Continuous effects
		ACCELERATION = 0,
		DECCELERATION,

		HEALTH_INCREASE,
		HEALTH_DECREASE,

		POWER_INCREASE,
		POWER_DECREASE,

		DEFENCE_INCREASE,
		DEFENCE_DECREASE,

		CONTINUOUS_DAMAGE,
		CONTINUOUS_HEALING,

		IMMORTALITY,
		SPIRITUAL_FORM,

		INVISIBILITY,

		// Instant effects
		HEAL,
		DAMAGE,

		RANDOM_TELEPORTATION,

		NUMBER_EFFECT_IDS
	};

public:
	constexpr EffectId() = delete;
	constexpr EffectId(Value value) noexcept : BasicId(value) {
		assert(value < NUMBER_EFFECT_IDS);
	}

	constexpr EffectId& operator=(EffectId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	constexpr bool isContinuous() const noexcept {
		return m_id < HEAL;
	}

	constexpr bool isPeriodic() const noexcept {
		return m_id >= CONTINUOUS_DAMAGE && m_id <= CONTINUOUS_HEALING;
	}

	constexpr bool isInstant() const noexcept {
		return m_id >= HEAL && m_id < NUMBER_EFFECT_IDS;
	}

	std::string toString() const override;
};