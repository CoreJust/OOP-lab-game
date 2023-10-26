// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstdint>

/*
*	Keys.h contains an enumeration of the virtual keys and mouse buttons.
*
*	They do not necessarily refer to the real keys and mouse buttons, but
*	are considered as such within the game.
*/

namespace io {
	// Virtual game keyboard representation
	// Two keys may actually refer to the same real key, or may not
	enum Key : uint8_t {
		KEY_UP = 0,
		KEY_LEFT,
		KEY_DOWN,
		KEY_RIGHT,

		KEY_ACCEL, // Acceleration
		KEY_SPACE, // Universal key
		KEY_ESCAPE,
		KEY_ENTER,

		NUMBER_KEYS
	};

	enum MouseButton : uint8_t {
		MOUSE_LMB = 0, // Left mouse button
		MOUSE_RMB, // Right mouse button

		MOUSE_WHEEL,

		NUMBER_MOUSE_BUTTONS
	};
}