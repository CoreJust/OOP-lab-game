#include "GlobalSettingsLoader.h"

#include "IO/Logger.h"

constexpr const char* GLOBAL_SETTINGS_FILE_NAME = "global_settings";

void io::GlobalSettingsLoader::load() {
	auto parseResult = JsonFileParser::parse(GLOBAL_SETTINGS_FILE_NAME);

	if (!parseResult.isOk()) {
		io::Logger::logError("Failure occured while loading global settings: " + parseResult.error() + ", default settings are set");
		return;
	}

	loadFromParsed(parseResult.extract());
}

void io::GlobalSettingsLoader::loadFromParsed(io::JsonValue value) {
	if (!value.isObject()) {
		io::Logger::logError("Invalid global settings file: an object expected");
		return;
	}

	for (const auto& [key, val] : value.asObject()) {
		if (val.isNull()) {
			continue;
		}

		if (key == "resources_location") {
			if (!val.isString()) {
				io::Logger::logError("Invalid global settings file: resources_location must be a string");
			} else {
				m_sets.m_texturesLocation = val.asString() + "img/";
				m_sets.m_audioLocation = val.asString() + "audio/";
				m_sets.m_shadersLocation = val.asString() + "shaders/";
				m_sets.m_fontsLocation = val.asString() + "fonts/";
			}
		} else if (key == "font") {
			if (!val.isString()) {
				io::Logger::logError("Invalid global settings file: font must be a string");
			} else {
				m_sets.m_textFont = val.asString();
			}
		} else if (key == "render_distance") {
			if (!val.isINumber() || val.asINumber() <= 0) {
				io::Logger::logError("Invalid global settings file: render_distance must be a whole number greater than zero");
			} else {
				m_sets.m_maxRenderDistance = val.asINumber();
			}
		} else if (key == "update_distance") {
			if (!val.isINumber() || val.asINumber() <= 0) {
				io::Logger::logError("Invalid global settings file: update_distance must be a whole number greater than zero");
			} else {
				m_sets.m_updateDistance = val.asINumber();
			}
		} else if (key == "input_mode") {
			if (!val.isString()) {
				io::Logger::logError("Invalid global settings file: input_mode must be a string");
			} else {
				if (val.asString() == "keyboard_and_mouse") {
					m_sets.m_inputMode = io::KEYBOARD_AND_MOUSE_INPUT;
				} else if (val.asString() == "file") {
					m_sets.m_inputMode = io::FILE_INPUT;
				} else {
					io::Logger::logError("Invalid global settings file: input_mode must be either of keyboard_and_mouse or file");
				}
			}
		} else if (key == "input_file") {
			if (!val.isString()) {
				io::Logger::logError("Invalid global settings file: input_file must be a string");
			} else {
				m_sets.m_inputFile = val.asString();
			}
		} else if (key == "save_input") {
			if (!val.isBool()) {
				io::Logger::logError("Invalid global settings file: save_input must be a boolean");
			} else {
				m_sets.m_isToSaveInput = val.asBool();
			}
		} else if (key == "log_input") {
			if (!val.isBool()) {
				io::Logger::logError("Invalid global settings file: log_input must be a boolean");
			} else {
				m_sets.m_isToLogInput = val.asBool();
			}
		} else if (key == "log_delta_time") {
			if (!val.isBool()) {
				io::Logger::logError("Invalid global settings file: log_delta_time must be a boolean");
			} else {
				m_sets.m_isToLogDeltaTime = val.asBool();
			}
		} else if (key == "log_settings") {
			if (!val.isBool()) {
				io::Logger::logError("Invalid global settings file: log_settings must be a boolean");
			} else {
				m_sets.m_isToLogSettings = val.asBool();
			}
		} else if (key == "log_entities_pos") {
			if (!val.isBool()) {
				io::Logger::logError("Invalid global settings file: log_entities_pos must be a boolean");
			} else {
				m_sets.m_isToLogEntitiesPos = val.asBool();
			}
		} else if (key == "log_entities_effects") {
			if (!val.isBool()) {
				io::Logger::logError("Invalid global settings file: log_entities_effects must be a boolean");
			} else {
				m_sets.m_isToLogEntitiesEffects = val.asBool();
			}
		} else {
			io::Logger::logError("Invalid global settings file: unknown setting: " + val.toString());
		}
	}

	if (m_sets.isToLogSettings()) {
		io::Logger::logInfo("Successfully loaded settings: " + value.toString());
	}
}
