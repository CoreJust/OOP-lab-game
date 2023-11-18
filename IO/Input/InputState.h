 // This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <bitset>
#include <string>
#include <string_view>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Math/Vector.h"

/*
*	InputState(.h/.cpp) contains a struct that represents the state of the input at the moment.
* 
*	It contains the delta time of the frame and the pressed keys/state of mouse.
*/

namespace io {
	struct InputState final {
		constexpr inline static size_t STRING_REPRESENTATION_SIZE =
			math::Cmath::ceil(sf::Keyboard::KeyCount / 8.f)
			+ math::Cmath::ceil(sf::Mouse::ButtonCount / 8.f)
			+ sizeof(math::Vector2f) // mouse position
			+ sizeof(float) // wheel delta
			+ sizeof(float); // frame delta time


		///  FIELDS  ///

		std::bitset<sf::Keyboard::KeyCount> keysState; // true if pressed and false otherwise
		std::bitset<sf::Mouse::ButtonCount> miceState; // true if pressed and false otherwise

		math::Vector2f mousePos;
		float mouseWheelDelta = 0.f;

		float deltaTime = 1.f;


		///  METHODS  ///

		std::string toString() const;
		bool loadFromString(std::string_view str);
	};
}