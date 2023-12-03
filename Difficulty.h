// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/EnumWrap.h"

/*
*	Difficulty.h contains a class that is a wrap over
*	an enumeration of possible difficulty levels.
*/

class Difficulty final : public utils::EnumWrap<uint8_t> {
public:
	enum Value : uint8_t {
		EASY = 0,
		NORMAL,
		HARD,
		EXTREME,
		NIGHTMARISH,

		NUMBER_DIFFICULTIES
	};

public:
	constexpr Difficulty() noexcept = default;
	constexpr Difficulty(const Value value) noexcept : utils::EnumWrap<uint8_t>(value) {
		assert(value < NUMBER_DIFFICULTIES);
	}

	constexpr Difficulty& operator=(const Difficulty other) noexcept {
		m_value = other;
		return *this;
	}

	inline std::string_view toString() const override {
		static const char* s_difficultyNames[] = {
			"easy",
			"normal",
			"hard",
			"extreme",
			"nightmarish",

			"NUMBER_DIFFICULTIES"
		};

		assert(m_value < std::size(s_difficultyNames));

		return s_difficultyNames[m_value];
	}
};