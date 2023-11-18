// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Window/Mouse.hpp>

#include "VirtualInput.h"
#include "IO/File/InputFileLoader.h"

/*
*	KeyboardMouseInput(.h/.cpp) contains a class that inherits VirtualInput and represents
*	the input from the mouse and keyboard.
*
*	It redirects the input scanning from the real keyboard and mouse into the virtual input.
*	The class also writes the input state to a file if such global setting is set.
*/

namespace io {
	// Implements the real keyboard/mouse input via SFML
	// Allows custom bindings for keyboard and mouse buttons, but only key for key and button for button
	// Doesn't allow bindings for mouse position / mouse wheel
	class KeyboardMouseInput final : public VirtualInput {
	private:
		InputFileLoader m_loader; // To write the input there if it is required

	public:
		KeyboardMouseInput(const float& mouseWheelDelta) noexcept;

		bool update(float& deltaTime) override;

		bool isKeyPressed(const Key key) const override;
		bool isKeyReleased(const Key key) const override;

		bool isMouseButtonPressed(const MouseButton btn) const override;
		bool isMouseButtonReleased(const MouseButton btn) const override;

		math::Vector2f getMousePosition() const override;
		float getMouseWheelDelta() const override;
	};
}