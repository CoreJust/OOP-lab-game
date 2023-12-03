// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/EnumWrap.h"

/*
*	InputMode.h contains a file that is a wrap over an
*	enumeration of possible input modes.
*/

namespace io {
	class InputMode final : public utils::EnumWrap<uint8_t> {
	public:
		enum Value : uint8_t {
			KEYBOARD_AND_MOUSE_INPUT = 0, // from keyboard and from mouse
			FILE_INPUT, // from a file

			NUMBER_INPUT_MODES
		};

	public:
		constexpr InputMode() noexcept = default;
		constexpr InputMode(const Value value) noexcept : utils::EnumWrap<uint8_t>(value) {
			assert(value < NUMBER_INPUT_MODES);
		}

		constexpr InputMode& operator=(const InputMode other) noexcept {
			m_value = other;
			return *this;
		}

		inline std::string_view toString() const override {
			static const char* s_difficultyNames[] = {
				"keyboard_and_mouse",
				"file",

				"NUMBER_INPUT_MODES"
			};

			assert(m_value < std::size(s_difficultyNames));

			return s_difficultyNames[m_value];
		}
	};
}