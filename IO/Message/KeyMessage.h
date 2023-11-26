// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "Message.h"
#include "IO/Input/Keys.h"
#include "IO/Input/KeysStringMap.h"

/*
*	KeyMessage.h contains a class for a message
*	of key being pressed and an action being executed.
*/

namespace io {
	class KeyMessage final : public Message {
	private:
		sf::Keyboard::Key m_realKey;
		Key m_commandExecuted;
		bool m_isPressed;

	private:
		inline static KeysStringMap s_keysStringMap;

	public:
		constexpr KeyMessage(
			const sf::Keyboard::Key realKey,
			const Key command,
			const bool isPressed,
			const std::source_location location = std::source_location::current()
		) noexcept : Message(location), m_realKey(realKey), m_commandExecuted(command), m_isPressed(isPressed) { }

		std::ostream& printTo(std::ostream& out) const override {
			if (m_isPressed) {
				return out << "Key pressed event, key: " << s_keysStringMap.realKeysReversed().at(m_realKey)
					<< ", command executed: " + s_keysStringMap.virtualKeysReversed().at(m_commandExecuted);
			} else {
				return out << "Key released event, key: " << s_keysStringMap.realKeysReversed().at(m_realKey)
					<< ", command executed: " + s_keysStringMap.virtualKeysReversed().at(m_commandExecuted);
			}
		}

		LogLevel getLogLevel() const override {
			return LogLevel::TRACE; // So as not to spam
		}

		friend std::ostream& operator<<(std::ostream& out, const KeyMessage& msg) {
			return msg.printTo(out);
		}
	};
}
