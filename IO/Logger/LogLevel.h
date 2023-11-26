// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/EnumWrap.h"

/*
*	LogLevel.h contains an enumeration of the logging levels.
*	The enumeration is wrapped in a class for convenience reasons.
* 
*	Each message in the logging system has a level, and only those
*	with level higher or egual to the global logging level are being
*	logged.
* 
*	There are four of them (from the highest logging level to the lowest, 
*	so the first one is being logged only if it it the global logging level):
*		TRACE - the highest logging level. Trace log messages are mostly not
*				important and are only used for tracing some other problems.
*		DEBUG - the messages that can be used for debugging but have no
*				importance as is.
*		INFO -  some useful information.
*		WARNING - something went not as expected/a dangerous situation occured,
*				and it is fine in general but can lead to some dire repercussions.
*		ERROR - an error occured, but the program can go on.
*		FATAL - a fatal error. The program crashes.
*/

namespace io {
	class LogLevel final : public utils::EnumWrap<uint8_t> {
	public:
		enum Value : uint8_t {
			TRACE,
			DEBUG,
			INFO,
			WARNING,
			ERROR,
			FATAL,

			UNREACHABLE, // The log level so serious that messages of it cannot exist

			NUMBER_LOG_LEVELS
		};

	public:
		constexpr LogLevel() noexcept = default;
		constexpr LogLevel(const Value value) noexcept : utils::EnumWrap<uint8_t>(value) {
			assert(value < NUMBER_LOG_LEVELS);
		}

		constexpr LogLevel& operator=(const LogLevel other) noexcept {
			m_value = other;
			return *this;
		}

		constexpr bool isMoreSeriousThan(const LogLevel other) const noexcept {
			return m_value > other;
		}

		// Returns true if this log level allows logging messages of the given level
		constexpr bool allowsLoggingOf(const LogLevel other) const noexcept {
			return m_value <= other;
		}

		inline std::string_view toString() const override {
			static const char* s_logLevelNames[] = {
				"[TRACE]",
				"[DEBUG]",
				"[INFO]",
				"[WARNING]",
				"[ERROR]",
				"[FATAL]",

				"NUMBER_LOG_LEVELS"
			};

			assert(m_value < std::size(s_logLevelNames));

			return s_logLevelNames[m_value];
		}
	};
}