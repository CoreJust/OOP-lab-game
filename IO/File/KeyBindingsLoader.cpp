// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "KeyBindingsLoader.h"

#include <map>
#include <bitset>

#include "GlobalSettings.h"
#include "IO/Logger.h"
#include "IO/Input/KeysStringMap.h"

void io::KeyBindingsLoader::load() {
	loadDefaultBindings();

	auto parseResult = JsonFileParser::parse(GlobalSettings::get().getBindingsFile());

	if (!parseResult.isOk()) {
		io::Logger::logError("Failure occured while loading key bindings: " + parseResult.error() + ", default bindings are set");
		return;
	}

	loadFromParsed(parseResult.extract());
}

void io::KeyBindingsLoader::loadDefaultBindings() {
	m_bindings.setBindings(
		{ sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D, 
		  sf::Keyboard::LShift, sf::Keyboard::Space, sf::Keyboard::Escape, sf::Keyboard::Enter },
		{ sf::Mouse::Left, sf::Mouse::Right, sf::Mouse::Middle }
	);
}

void io::KeyBindingsLoader::loadFromParsed(io::JsonValue value) {
	if (!value.isObject()) {
		io::Logger::logError("Invalid key bindings file: an object expected");
		return;
	}

	sf::Keyboard::Key keys[Key::NUMBER_KEYS];
	sf::Mouse::Button mice[MouseButton::NUMBER_MOUSE_BUTTONS];

	std::bitset<sf::Keyboard::KeyCount> usedRealKeys;
	std::bitset<sf::Mouse::ButtonCount> usedRealMouseButtons;

	for (auto& key : keys) key = sf::Keyboard::KeyCount;
	for (auto& mouse : mice) mouse = sf::Mouse::ButtonCount;

	KeysStringMap ksMap;

	// The actual json processing is here
	for (const auto& [key, val] : value.asObject()) {
		if (val.isNull()) {
			continue;
		}

		if (!val.isString()) {
			io::Logger::logError("Invalid key bindings file: a string expected as a value of a binding, got: " + val.toString());
			return;
		}

		if (ksMap.virtualKeys().contains(key)) {
			Key binding = ksMap.virtualKeys().at(key);
			if (keys[binding] != sf::Keyboard::KeyCount) {
				io::Logger::logError("Invalid key bindings file: binding duplicate: " + key);
				return;
			}

			if (!ksMap.realKeys().contains(val.asString())) {
				io::Logger::logError("Invalid key bindings file: no such real key: " + val.asString());
				return;
			}

			keys[binding] = ksMap.realKeys().at(val.asString());
			if (usedRealKeys.test(keys[binding])) { // Real key reusage
				io::Logger::logError("Invalid key bindings file: real binding duplicate: " + val.toString());
				return;
			} else {
				usedRealKeys.set(keys[binding]);
			}
		} else if (ksMap.virtualMouse().contains(key)) {
			MouseButton binding = ksMap.virtualMouse().at(key);
			if (mice[binding] != sf::Mouse::ButtonCount) {
				io::Logger::logError("Invalid key bindings file: mouse binding duplicate: " + key);
				return;
			}

			if (!ksMap.realMouse().contains(val.asString())) {
				io::Logger::logError("Invalid key bindings file: no such real mouse key: " + val.asString());
				return;
			}

			mice[binding] = ksMap.realMouse().at(val.asString());
			if (usedRealMouseButtons.test(mice[binding])) { // Real mouse button reusage
				io::Logger::logError("Invalid key bindings file: real mouse binding duplicate: " + val.toString());
				return;
			} else {
				usedRealMouseButtons.set(mice[binding]);
			}
		}
	}

	if (std::find(std::begin(keys), std::end(keys), Key::NUMBER_KEYS) != std::end(keys)
		|| std::find(std::begin(mice), std::end(mice), MouseButton::NUMBER_MOUSE_BUTTONS) != std::end(mice)) {
		io::Logger::logError("Invalid bindings: not all the keys/mouse buttons defined");
		return;
	}

	io::Logger::logInfo("Loaded bindings successfully");
	m_bindings.updateBindings(keys, mice);
}
