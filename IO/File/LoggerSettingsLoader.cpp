// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "LoggerSettingsLoader.h"

constexpr const char* LOGGER_SETTINGS_FILE_NAME = "log_settings";

utils::Result<utils::Void> io::LoggerSettingsLoader::load() {
	loadDefault();

	auto parseResult = JsonFileParser::parse(LOGGER_SETTINGS_FILE_NAME);
	if (!parseResult.isOk()) {
		return utils::Failure("failure occured while loading logger settings: " + parseResult.error() + ", default settings are set");
	}

	auto result = loadFromParsed(parseResult.extract());
	if (!result.isOk()) {
		loadDefault();
	}

	return result;
}

void io::LoggerSettingsLoader::loadDefault() {
	m_settings = Logger::Settings {
		.logDateFrom = LogLevel::ERROR,
		.logTimeFrom = LogLevel::TRACE,
		.logSourceLocationFrom = LogLevel::WARNING,
		.loggingLevel = LogLevel::INFO
	};

	m_targets.clear();
	m_targets.emplace_back(LogTarget::CONSOLE);
}

utils::Result<utils::Void> io::LoggerSettingsLoader::loadFromParsed(io::JsonValue value) {
	if (!value.isObject()) {
		return utils::Failure("Invalid logger settings file: must be an object, got " + value.toString());
	}

	for (const auto& [key, val] : value.asObject()) {
		if (val.isNull()) {
			continue; // Leave default
		}

		if (key == "targets") { // The only one with a non-string value
			if (!val.isArray()) {
				return utils::Failure("Invalid logger settings file: targets' value is expected to be an array, got " + val.toString());
			}

			m_targets.clear();
			for (auto& trg : val.asArray()) {
				if (!trg.isString()) {
					return utils::Failure("Invalid logger settings file: a target must be a string, got " + trg.toString());
				}

				if (trg.asString() == "console") {
					m_targets.emplace_back(LogTarget::CONSOLE);
				} else { // a file
					m_targets.emplace_back(LogTarget::FILE, trg.asString());
				}
			}

			continue;
		}

		if (!val.isString()) {
			return utils::Failure("Invalid logger settings file: values are expected to be a string, got " + val.toString());
		}

		LogLevel logLevel = LogLevel::UNREACHABLE;
		if (val.asString() == "trace") {
			logLevel = LogLevel::TRACE;
		} else if (val.asString() == "debug") {
			logLevel = LogLevel::DEBUG;
		} else if (val.asString() == "info") {
			logLevel = LogLevel::INFO;
		} else if (val.asString() == "warning") {
			logLevel = LogLevel::WARNING;
		} else if (val.asString() == "error") {
			logLevel = LogLevel::ERROR;
		} else if (val.asString() == "fatal") {
			logLevel = LogLevel::FATAL;
		} else if (val.asString() == "unreachable") {
			logLevel = LogLevel::UNREACHABLE;
		} else {
			return utils::Failure("Invalid logger settings file: unknown logging level " + val.asString());
		}

		if (key == "logging_level") {
			m_settings.loggingLevel = logLevel;
		} else if (key == "log_date_from_level") {
			m_settings.logDateFrom = logLevel;
		} else if (key == "log_time_from_level") {
			m_settings.logTimeFrom = logLevel;
		} else if (key == "log_source_from_level") {
			m_settings.logSourceLocationFrom = logLevel;
		} else {
			return utils::Failure("Invalid logger settings file : unknown setting " + key);
		}
	}

	return utils::Success();
}
