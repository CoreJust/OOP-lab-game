// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/EnumWrap.h"

/*
*	Alignment.h contains a class that is a wrap over
*	an enumeration of possible alignments of GameGui
*	that use ImGui (i.e. via ImGuiApi class).
*/

class Alignment final : public utils::EnumWrap<uint8_t> {
public:
	enum Value : uint8_t {
		// Default ImGui alignment - to the left
		LEFT = 0,

		// Centered elements
		CENTERED,

		// The element label goes from the center to the left,
		// while element goes to the right
		CENTERED_BY_ELEMENTS,

		NUMBER_ALIGNMENTS
	};

public:
	constexpr Alignment() noexcept = default;
	constexpr Alignment(const Value value) noexcept : utils::EnumWrap<uint8_t>(value) {
		assert(value < NUMBER_ALIGNMENTS);
	}

	constexpr Alignment& operator=(const Alignment other) noexcept {
		m_value = other;
		return *this;
	}

	inline std::string_view toString() const override {
		static const char* s_difficultyNames[] = {
			"LEFT",
			"CENTERED",
			"CENTERED_BY_ELEMENTS",

			"NUMBER_ALIGNMENTS"
		};

		assert(m_value < std::size(s_difficultyNames));

		return s_difficultyNames[m_value];
	}
};