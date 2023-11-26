// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "IO/Json/JsonFileParser.h"
#include "IO/Logger/Logger.h"

/*
*	LoggerSettingsLoader(.h/.cpp) contains a class that loads the logger
*	settings, namely logging level and log targets, from a file.
* 
*	Sample file:
*	{
*		"logging_level": "trace",
*		"log_date_from_level": "error",
*		"log_time_from_level": "trace",
*		"log_source_from_level": "error",
*		"targets": [
*			"console",
*			"OOP_lab6_log.txt"
*		]
*	}
*/

namespace io {
	class LoggerSettingsLoader final : public JsonFileParser {
	private:
		Logger::Settings& m_settings;
		std::vector<LogTarget>& m_targets;

	public:
		constexpr LoggerSettingsLoader(Logger::Settings& sets, std::vector<LogTarget>& trgs) noexcept
			: m_settings(sets), m_targets(trgs) { }

		utils::Result<utils::Void> load();
		void loadDefault();

	private:
		utils::Result<utils::Void> loadFromParsed(io::JsonValue value);
	};
}