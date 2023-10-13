// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "KeyboardMouseInput.h"

io::KeyboardMouseInput::KeyboardMouseInput(const float& mouseWheelDelta) noexcept
	: m_keyBindings({ sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D,
					sf::Keyboard::LShift, sf::Keyboard::Space, sf::Keyboard::Escape, sf::Keyboard::Enter }),
	m_mouseButtonBindings({ sf::Mouse::Left, sf::Mouse::Right, sf::Mouse::Middle }),
	m_mouseWheelDelta(mouseWheelDelta) { }

io::KeyboardMouseInput::KeyboardMouseInput(KeyBindings keyBindings, MouseButtonBindings mouseButtonBindings, const float& mouseWheelDelta) noexcept
	: m_keyBindings(std::move(keyBindings)), m_mouseButtonBindings(std::move(mouseButtonBindings)), m_mouseWheelDelta(mouseWheelDelta) { }

bool io::KeyboardMouseInput::isKeyPressed(const Key key) const {
	return sf::Keyboard::isKeyPressed(m_keyBindings[key]);
}

bool io::KeyboardMouseInput::isKeyReleased(const Key key) const {
	return !sf::Keyboard::isKeyPressed(m_keyBindings[key]);
}

bool io::KeyboardMouseInput::isMouseButtonPressed(const MouseButton btn) const {
	return sf::Mouse::isButtonPressed(m_mouseButtonBindings[btn]);
}

bool io::KeyboardMouseInput::isMouseButtonReleased(const MouseButton btn) const {
	return !sf::Mouse::isButtonPressed(m_mouseButtonBindings[btn]);
}

math::Vector2f io::KeyboardMouseInput::getMousePosition() const {
	auto pos = sf::Mouse::getPosition();
	return math::Vector2f(pos.x, pos.y);
}

float io::KeyboardMouseInput::getMouseWheelDelta() const {
	return m_mouseWheelDelta;
}
