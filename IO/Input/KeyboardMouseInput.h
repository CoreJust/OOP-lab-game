#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "VirtualInput.h"

namespace io {
	// Implements the real keyboard/mouse input via SFML
	// Allows custom bindings for keyboard and mouse buttons, but only key for key and button for button
	// Doesn't allow bindings for mouse position / mouse wheel
	class KeyboardMouseInput final : public VirtualInput {
	public:
		struct KeyBindings final {
			sf::Keyboard::Key bindings[Key::NUMBER_KEYS];

			constexpr KeyBindings(const KeyBindings& other) noexcept = default;
			constexpr KeyBindings(KeyBindings&& other) noexcept = default;

			inline KeyBindings(const sf::Keyboard::Key(&arr)[Key::NUMBER_KEYS]) {
				memcpy(bindings, arr, sizeof(bindings));
			}

			constexpr sf::Keyboard::Key operator[](const Key key) const noexcept {
				return bindings[key];
			}
		};

		struct MouseButtonBindings final {
			sf::Mouse::Button bindings[MouseButton::NUMBER_MOUSE_BUTTONS];

			constexpr MouseButtonBindings(const MouseButtonBindings& other) noexcept = default;
			constexpr MouseButtonBindings(MouseButtonBindings&& other) noexcept = default;

			inline MouseButtonBindings(const sf::Mouse::Button(&arr)[MouseButton::NUMBER_MOUSE_BUTTONS]) {
				memcpy(bindings, arr, sizeof(bindings));
			}

			constexpr sf::Mouse::Button operator[](const MouseButton btn) const noexcept {
				return bindings[btn];
			}
		};

	private:
		KeyBindings m_keyBindings;
		MouseButtonBindings m_mouseButtonBindings;
		const float& m_mouseWheelDelta;

	public:
		KeyboardMouseInput(const float& mouseWheelDelta) noexcept;
		KeyboardMouseInput(KeyBindings keyBindings, MouseButtonBindings mouseButtonBindings, const float& mouseWheelDelta) noexcept;

		bool isKeyPressed(const Key key) const override;
		bool isKeyReleased(const Key key) const override;

		bool isMouseButtonPressed(const MouseButton btn) const override;
		bool isMouseButtonReleased(const MouseButton btn) const override;

		math::Vector2f getMousePosition() const override;
		float getMouseWheelDelta() const override;
	};
}