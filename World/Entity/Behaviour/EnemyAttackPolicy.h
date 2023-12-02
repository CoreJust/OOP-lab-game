// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/EnumWrap.h"

/*
*	EnemyAttackPolicy.h contains a class that is a wrap over
*	an enumeration of all the possible attack policies of an enemy.
* 
*	Attack policy defines how the enemy reacts upon seeing a player.
*/

class EnemyAttackPolicy final : public utils::EnumWrap<uint8_t> {
public:
	enum Value : uint8_t {
		IGNORE = 0, // Enemy doesn't react on player

		// Enemy goes directly towards the player only as long as it sees them
		// But the enemy returns to roaming as long as player is out of sight
		PASSIVE_PURSUIT,

		// Enemy goes directly towards the player only as long as it sees them
		// If the player is out of sight, the enemy goes to the last place it had seen them
		INERTIAL_PURSUIT,

		// After the enemy has noticed the player, it would follow him and look for a path to the player
		// The only way to stop the pursuit is to either leave the enemy out of the update distance
		// or leave the second range that defines for how far would it continue the pursuit
		PROACTIVE_PURSUIT,

		NUMBER_ENEMY_ATTACK_POLICIES
	};

public:
	constexpr EnemyAttackPolicy() noexcept = default;
	constexpr EnemyAttackPolicy(const Value val) noexcept : utils::EnumWrap<uint8_t>(val) {
		assert(val < NUMBER_ENEMY_ATTACK_POLICIES);
	}

	constexpr EnemyAttackPolicy& operator=(const EnemyAttackPolicy other) noexcept {
		m_value = other.m_value;
		return *this;
	}

	inline std::string_view toString() const override {
		static const char* s_enemyAttackPolicyNames[] = {
			"IGNORE",
			"PASSIVE_PURSUIT",
			"INERTIAL_PURSUIT",
			"PROACTIVE_PURSUIT",

			"NUMBER_ENEMY_ATTACK_POLICIES"
		};

		assert(m_value < std::size(s_enemyAttackPolicyNames));

		return s_enemyAttackPolicyNames[m_value];
	}
};