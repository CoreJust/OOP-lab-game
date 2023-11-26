// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <iostream>
#include <fstream>
#include "Utils/EnumWrap.h"

/*
*	LogTarget.h contains a class that implements an output target
*	for logging.
* 
*	Several logging targets may be used (allthough not in a single 
*	instance of LogTarget), so the logger would log simultaneously
*	into several targets.
*/

namespace io {
	class LogTarget final : public utils::EnumWrap<uint8_t> {
	public:
		enum Value : uint8_t {
			CONSOLE,
			FILE,

			NUMBER_LOG_TARGETS
		};

	private:
		std::unique_ptr<std::ofstream> m_file; // Empty in console mode

	public:
		LogTarget() noexcept = delete;
		LogTarget(const LogTarget&) noexcept = delete;
		LogTarget(LogTarget&&) noexcept = default;
		constexpr LogTarget(const Value value) noexcept : utils::EnumWrap<uint8_t>(value) {
			assert(value == CONSOLE);
		}

		inline LogTarget(const Value value, const std::string& filename) 
			: utils::EnumWrap<uint8_t>(value), m_file(std::make_unique<std::ofstream>(filename)) {
			assert(value == FILE);
		}

		inline std::ostream& target() {
			switch (m_value) {
				case CONSOLE: return std::clog;
				case FILE: return *m_file;
			default: break;
			}

			assert(false && "unreachable");
		}

		inline std::string_view toString() const override {
			static const char* s_logLevelNames[] = {
				"CONSOLE",
				"FILE",

				"NUMBER_LOG_TARGETS"
			};

			assert(m_value < std::size(s_logLevelNames));

			return s_logLevelNames[m_value];
		}
	};
}