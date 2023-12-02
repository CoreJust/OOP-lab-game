// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <ostream>
#include <chrono>
#include <source_location>
#include <concepts>
#include "IO/Logger/LogLevel.h"

/*
*	Message.h contains a basic class for messages.
* 
*	A message is created somewhere in the code and being sent
*	to the logger, which would, right away or with a delay,
*	log the message.
* 
*	A message contains some information about itself, but no 
*	string - the text is being formed the moment the message is
*	logged, no earlier.
*/

namespace io {
	class Message {
	protected:
		std::chrono::system_clock::time_point m_creationTime;
		std::source_location m_location;

	protected:
		constexpr Message(std::source_location location) noexcept 
			: m_location(std::move(location)) {
			if (std::is_constant_evaluated()) {
				m_creationTime = std::chrono::system_clock::time_point();
			} else {
				m_creationTime = std::chrono::system_clock::now();
			}
		}

		virtual std::ostream& printTo(std::ostream& out) const = 0;

	public:
		virtual LogLevel getLogLevel() const {
			return LogLevel::INFO; // Default
		}

		constexpr const std::chrono::system_clock::time_point& getCreationTime() const noexcept {
			return m_creationTime;
		}

		constexpr const std::source_location& getLocation() const noexcept {
			return m_location;
		}
		
		friend std::ostream& operator<<(std::ostream& out, const Message& msg) {
			return msg.printTo(out);
		}
	};

	/*
	template<class T>
	concept MessageClass = std::is_base_of_v<Message, T>&& requires(T msg, std::ostream& out) { 
		{ out << msg } -> std::same_as<std::ostream&>;
	};
	*/
}
