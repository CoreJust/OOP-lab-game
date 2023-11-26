// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Message.h"
#include "World/Entity/EntityStats.h"

/*
*	PlayerWonMessage.h contains a class for a message
*	of player win, that contains the player's stats.
*
*	Since there is no true win currently in the game,
*	this message is expected to be sent on reaching
*	another level.
*/

namespace io {
	class PlayerWonMessage final : public Message {
	private:
		EntityStats m_stats;
		float m_health;

	public:
		constexpr PlayerWonMessage(
			EntityStats playerStats,
			const float health,
			const std::source_location location = std::source_location::current()
		) noexcept : Message(location), m_stats(std::move(playerStats)), m_health(health) { }

		std::ostream& printTo(std::ostream& out) const override {
			return out << "Player won(?), the stats are " << m_stats.toString(m_health);
		}

		friend std::ostream& operator<<(std::ostream& out, const PlayerWonMessage& msg) {
			return msg.printTo(out);
		}
	};
}
