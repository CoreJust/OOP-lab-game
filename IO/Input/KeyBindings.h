// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Keys.h"

/*
*	KeyBindings.h contains a class that represents the bindings of keyboard's and mouse's keys.
* 
*	Bindings allows to translate the actual user input, be it from the keyboard, file, or 
*	anything else, to the abstract internal commands (the VirtualInput).
*/

namespace io {
	struct KeyBindings final {
	private:
		sf::Keyboard::Key m_keyBindings[Key::NUMBER_KEYS];
		sf::Mouse::Button m_mouseBindings[MouseButton::NUMBER_MOUSE_BUTTONS];

	public:
		constexpr KeyBindings() noexcept = default;
		constexpr KeyBindings(const KeyBindings& other) noexcept = default;
		constexpr KeyBindings(KeyBindings&& other) noexcept = default;

		inline KeyBindings(const sf::Keyboard::Key(&keys)[Key::NUMBER_KEYS], 
						   const sf::Mouse::Button(&mice)[MouseButton::NUMBER_MOUSE_BUTTONS]) {
			setBindings(keys, mice);
		}

		constexpr sf::Keyboard::Key getKey(const Key key) const noexcept {
			return m_keyBindings[key];
		}

		constexpr sf::Mouse::Button getMouseButton(const MouseButton btn) const noexcept {
			return m_mouseBindings[btn];
		}

		constexpr void updateBindings(const sf::Keyboard::Key(&keys)[Key::NUMBER_KEYS],
									  const sf::Mouse::Button(&mice)[MouseButton::NUMBER_MOUSE_BUTTONS]) {
			for (size_t i = 0; i < Key::NUMBER_KEYS; i++) {
				if (keys[i] != sf::Keyboard::KeyCount) {
					m_keyBindings[i] = keys[i];
				}
			}

			for (size_t i = 0; i < MouseButton::NUMBER_MOUSE_BUTTONS; i++) {
				if (mice[i] != sf::Mouse::ButtonCount) {
					m_mouseBindings[i] = mice[i];
				}
			}
		}

		inline void setBindings(const sf::Keyboard::Key(&keys)[Key::NUMBER_KEYS],
								const sf::Mouse::Button(&mice)[MouseButton::NUMBER_MOUSE_BUTTONS]) {
			memcpy(m_keyBindings, keys, sizeof(m_keyBindings));
			memcpy(m_mouseBindings, mice, sizeof(m_mouseBindings));
		}
	};
}