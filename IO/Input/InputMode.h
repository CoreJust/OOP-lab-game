// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstdint>

/*
*	InputMode.h contains an enumeration of possible input modes.
*/

namespace io {
	enum InputMode : uint8_t {
		KEYBOARD_AND_MOUSE_INPUT = 0, // from keyboard and from mouse
		FILE_INPUT // from a file
	};
}