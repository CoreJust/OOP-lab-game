// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "KeyboardMouseInput.h"

io::KeyboardMouseInput::KeyboardMouseInput(const float& mouseWheelDelta) noexcept
	: m_mouseWheelDelta(mouseWheelDelta) { }

bool io::KeyboardMouseInput::isKeyPressed(const Key key) const {
	return sf::Keyboard::isKeyPressed(m_keyBindings.getKey(key));
}

bool io::KeyboardMouseInput::isKeyReleased(const Key key) const {
	return !sf::Keyboard::isKeyPressed(m_keyBindings.getKey(key));
}

bool io::KeyboardMouseInput::isMouseButtonPressed(const MouseButton btn) const {
	return sf::Mouse::isButtonPressed(m_keyBindings.getMouseButton(btn));
}

bool io::KeyboardMouseInput::isMouseButtonReleased(const MouseButton btn) const {
	return !sf::Mouse::isButtonPressed(m_keyBindings.getMouseButton(btn));
}

math::Vector2f io::KeyboardMouseInput::getMousePosition() const {
	auto pos = sf::Mouse::getPosition();
	return math::Vector2f(pos.x, pos.y);
}

float io::KeyboardMouseInput::getMouseWheelDelta() const {
	return m_mouseWheelDelta;
}
