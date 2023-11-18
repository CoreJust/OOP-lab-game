// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "KeyboardMouseInput.h"

#include "GlobalSettings.h"

io::KeyboardMouseInput::KeyboardMouseInput(const float& mouseWheelDelta) noexcept
	: VirtualInput(mouseWheelDelta),
	m_loader(GlobalSettings::get().isToSaveInput() ? GlobalSettings::get().getInputFile() : "", /* is reading = */false)
	{ }

bool io::KeyboardMouseInput::update(float& deltaTime) {
	if (m_loader.isOpen()) {
		for (uint8_t key = 0; key < sf::Keyboard::KeyCount; key++) {
			m_loader.state().keysState.set(key, sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)));
		}

		for (uint8_t btn = 0; btn < sf::Mouse::ButtonCount; btn++) {
			m_loader.state().miceState.set(btn, sf::Mouse::isButtonPressed(sf::Mouse::Button(btn)));
		}

		m_loader.state().mousePos = getMousePosition();
		m_loader.state().mouseWheelDelta = getMouseWheelDelta();

		m_loader.state().deltaTime = deltaTime;

		m_loader.write();
	}

	return false; // Why switching to itself?
}

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
