// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <map>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Keys.h"

/*
*	KeysStringMap.h contains a class that allows to convert a key to string and vice versa.
*/

namespace io {
	class KeysStringMap final {
	private:
		std::map<std::string, sf::Keyboard::Key> m_realKeysMap; // Supported real keys
		std::map<std::string, sf::Mouse::Button> m_realMouseMap; // Supported mouse buttons
		std::map<std::string, Key> m_virtualKeysMap; // Virtual key commands
		std::map<std::string, MouseButton> m_virtualMouseMap; // Virtual mouse button commands

		std::map<sf::Keyboard::Key, std::string> m_realKeysMapReversed;
		std::map<sf::Mouse::Button, std::string> m_realMouseMapReversed;
		std::map<Key, std::string> m_virtualKeysMapReversed;
		std::map<MouseButton, std::string> m_virtuallMouseMapReversed;

	public:
		KeysStringMap();

		const std::map<std::string, sf::Keyboard::Key>& realKeys() const;
		const std::map<std::string, sf::Mouse::Button>& realMouse() const;
		const std::map<std::string, Key>& virtualKeys() const;
		const std::map<std::string, MouseButton>& virtualMouse() const;

		const std::map<sf::Keyboard::Key, std::string>& realKeysReversed() const;
		const std::map<sf::Mouse::Button, std::string>& realMouseReversed() const;
		const std::map<Key, std::string>& virtualKeysReversed() const;
		const std::map<MouseButton, std::string>& virtualMouseReversed() const;
	};
}
