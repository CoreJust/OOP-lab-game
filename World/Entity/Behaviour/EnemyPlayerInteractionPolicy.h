// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/EnumWrap.h"

/*
*	EnemyPlayerInteractionPolicy.h contains a class that is a wrap over
*	an enumeration of all the possible actions of the enemy upon
*	reaching the player.
*/

class EnemyPlayerInteractionPolicy final : public utils::EnumWrap<uint8_t> {
public:
	enum Value : uint8_t {
		NORMAL_HIT = 0, // The default action of damaging the player
		POISONING,
		SHOCKING, // Immobilizes and blinds the player for some time

		SELF_DESTRUCT, // Kills itself and converts all of own HP into damage

		NUMBER_ENEMY_PLAYER_INTERACTION_POLICIES
	};

public:
	constexpr EnemyPlayerInteractionPolicy() noexcept = default;
	constexpr EnemyPlayerInteractionPolicy(const Value val) noexcept : utils::EnumWrap<uint8_t>(val) {
		assert(val < NUMBER_ENEMY_PLAYER_INTERACTION_POLICIES);
	}

	constexpr EnemyPlayerInteractionPolicy& operator=(const EnemyPlayerInteractionPolicy other) noexcept {
		m_value = other.m_value;
		return *this;
	}

	inline std::string_view toString() const override {
		static const char* s_enemyPlayerInteractionPolicyNames[] = {
			"NORMAL_HIT",
			"POISONING",
			"SHOCKING",

			"SELF_DESTRUCT",

			"NUMBER_ENEMY_PLAYER_INTERACTION_POLICIES"
		};

		assert(m_value < std::size(s_enemyPlayerInteractionPolicyNames));

		return s_enemyPlayerInteractionPolicyNames[m_value];
	}
};