// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/EnumWrap.h"

/*
*	EnemyMovePolicy.h contains a class that is a wrap over
*	an enumeration of all the possible move policies of an enemy.
* 
*	Move policy defines the behaviour of an entity when there is
*	no player or other attraction around.
*/

class EnemyMovePolicy final : public utils::EnumWrap<uint8_t> {
public:
	enum Value : uint8_t {
		NO_MOVING = 0, // Enemy doesn't move
		RANDOM_ROAMING, // Enemy roams around
		STRAIGHT_ROAMING, // Enemy roams around, but only in direct lines
		CLOSING_ON_PLAYER, // Enemy roams around, but with a priority of moving towards the player

		NUMBER_ENEMY_MOVE_POLICIES
	};

public:
	constexpr EnemyMovePolicy() noexcept = default;
	constexpr EnemyMovePolicy(const Value val) noexcept : utils::EnumWrap<uint8_t>(val) {
		assert(val < NUMBER_ENEMY_MOVE_POLICIES);
	}

	constexpr EnemyMovePolicy& operator=(const EnemyMovePolicy other) noexcept {
		m_value = other.m_value;
		return *this;
	}

	inline std::string_view toString() const override {
		static const char* s_enemyMovePolicyNames[] = {
			"NO_MOVING",
			"RANDOM_ROAMING",
			"STRAIGHT_ROAMING",
			"CLOSING_ON_PLAYER",

			"NUMBER_ENEMY_MOVE_POLICIES"
		};

		assert(m_value < std::size(s_enemyMovePolicyNames));

		return s_enemyMovePolicyNames[m_value];
	}
};