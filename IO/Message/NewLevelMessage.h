// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Message.h"
#include "Math/Vector.h"

/*
*	NewLevelMessage.h contains a class for a message
*	of new level creation, that contains the world's 
*	size and the player's position.
*/

namespace io {
	class NewLevelMessage final : public Message {
	private:
		math::Vector2u m_worldSize;
		math::Vector2f m_playerPos;

	public:
		constexpr NewLevelMessage(
			const math::Vector2u& worldSize,
			const math::Vector2f& playerPos,
			const std::source_location location = std::source_location::current()
		) noexcept : Message(location), m_worldSize(worldSize), m_playerPos(playerPos) { }

		std::ostream& printTo(std::ostream& out) const override {
			return out << "New level loaded, the level size is " << m_worldSize.toString() 
				<< " and the player is at " << m_playerPos.toString();
		}

		friend std::ostream& operator<<(std::ostream& out, const NewLevelMessage& msg) {
			return msg.printTo(out);
		}
	};
}
