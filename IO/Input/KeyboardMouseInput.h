#pragma once
#include <SFML/Window/Mouse.hpp>
#include "VirtualInput.h"

/*
*	KeyboardMouseInput(.h/.cpp) contains a class that inherits VirtualInput and represents
*	the input from the mouse and keyboard.
*
*	It redirects the input scanning from the real keyboard and mouse into the virtual input.
*/

namespace io {
	// Implements the real keyboard/mouse input via SFML
	// Allows custom bindings for keyboard and mouse buttons, but only key for key and button for button
	// Doesn't allow bindings for mouse position / mouse wheel
	class KeyboardMouseInput final : public VirtualInput {
	private:
		const float& m_mouseWheelDelta;

	public:
		KeyboardMouseInput(const float& mouseWheelDelta) noexcept;

		bool isKeyPressed(const Key key) const override;
		bool isKeyReleased(const Key key) const override;

		bool isMouseButtonPressed(const MouseButton btn) const override;
		bool isMouseButtonReleased(const MouseButton btn) const override;

		math::Vector2f getMousePosition() const override;
		float getMouseWheelDelta() const override;
	};
}