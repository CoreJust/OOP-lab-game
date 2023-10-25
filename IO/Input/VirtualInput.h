#pragma once
#include <cstdint>
#include "Math/Vector.h"

namespace io {
	// Basic class for all the input classes
	// An interface that allows to get user input as if from keyboard and mouse
	// Might have implementations (via inheritance) that would in fact use network or file for input
	class VirtualInput {
	public:
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

	public:
		virtual ~VirtualInput() noexcept = default;

		virtual bool isKeyPressed(const Key key) const = 0;
		virtual bool isKeyReleased(const Key key) const = 0;

		virtual bool isMouseButtonPressed(const MouseButton btn) const = 0;
		virtual bool isMouseButtonReleased(const MouseButton btn) const = 0;

		virtual math::Vector2f getMousePosition() const = 0;
		virtual float getMouseWheelDelta() const = 0;
	};
}