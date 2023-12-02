// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Message.h"
#include "Math/Vector.h"

/*
*	PlayerLostMessage.h contains a class for a message
*	of player loss, that contains the player's position.
*/

namespace io {
	class PlayerLostMessage final : public Message {
	private:
		math::Vector2f m_pos;

	protected:
		inline std::ostream& printTo(std::ostream& out) const override {
			return out << "Player lost at " << m_pos.to<int>().toString();
		}

	public:
		constexpr PlayerLostMessage(
			const math::Vector2f& pos,
			const std::source_location location = std::source_location::current()
		) noexcept : Message(location), m_pos(pos) { }
	};
}
