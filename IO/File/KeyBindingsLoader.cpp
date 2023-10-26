#include "KeyBindingsLoader.h"

#include <map>

#include "GlobalSettings.h"
#include "IO/Logger.h"

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

	std::map<std::string, sf::Keyboard::Key> realKeysMap = { // Supported real keys
		{ "up", sf::Keyboard::Up },
		{ "left", sf::Keyboard::Left },
		{ "down", sf::Keyboard::Down },
		{ "right", sf::Keyboard::Right },

		{ "w", sf::Keyboard::W },
		{ "a", sf::Keyboard::A },
		{ "s", sf::Keyboard::S },
		{ "d", sf::Keyboard::D },
		{ "b", sf::Keyboard::B },
		{ "c", sf::Keyboard::C },
		{ "e", sf::Keyboard::E },
		{ "f", sf::Keyboard::F },
		{ "g", sf::Keyboard::G },
		{ "h", sf::Keyboard::H },
		{ "i", sf::Keyboard::I },
		{ "j", sf::Keyboard::J },
		{ "k", sf::Keyboard::K },
		{ "l", sf::Keyboard::L },
		{ "m", sf::Keyboard::M },
		{ "n", sf::Keyboard::N },
		{ "o", sf::Keyboard::O },
		{ "p", sf::Keyboard::P },
		{ "q", sf::Keyboard::Q },
		{ "r", sf::Keyboard::R },
		{ "t", sf::Keyboard::T },
		{ "u", sf::Keyboard::U },
		{ "v", sf::Keyboard::V },
		{ "x", sf::Keyboard::X },
		{ "y", sf::Keyboard::Y },
		{ "z", sf::Keyboard::Z },

		{ "enter", sf::Keyboard::Enter },
		{ "space", sf::Keyboard::Space },
		{ "backspace", sf::Keyboard::BackSpace },
		{ "left_shift", sf::Keyboard::LShift },
		{ "right_shift", sf::Keyboard::RShift },
		{ "left_control", sf::Keyboard::LControl },
		{ "right_control", sf::Keyboard::RControl },
		{ "left_alt", sf::Keyboard::LAlt },
		{ "right_alt", sf::Keyboard::RAlt },
		{ "tab", sf::Keyboard::Tab },
		{ "escape", sf::Keyboard::Escape },

		{ "0", sf::Keyboard::Num0 },
		{ "1", sf::Keyboard::Num1 },
		{ "2", sf::Keyboard::Num2 },
		{ "3", sf::Keyboard::Num3 },
		{ "4", sf::Keyboard::Num4 },
		{ "5", sf::Keyboard::Num5 },
		{ "6", sf::Keyboard::Num6 },
		{ "7", sf::Keyboard::Num7 },
		{ "8", sf::Keyboard::Num8 },
		{ "9", sf::Keyboard::Num9 },

		{ "numpad0", sf::Keyboard::Numpad0 },
		{ "numpad1", sf::Keyboard::Numpad1 },
		{ "numpad2", sf::Keyboard::Numpad2 },
		{ "numpad3", sf::Keyboard::Numpad3 },
		{ "numpad4", sf::Keyboard::Numpad4 },
		{ "numpad5", sf::Keyboard::Numpad5 },
		{ "numpad6", sf::Keyboard::Numpad6 },
		{ "numpad7", sf::Keyboard::Numpad7 },
		{ "numpad8", sf::Keyboard::Numpad8 },
		{ "numpad9", sf::Keyboard::Numpad9 },

		{ "[", sf::Keyboard::LBracket },
		{ "]", sf::Keyboard::RBracket },
		{ ";", sf::Keyboard::SemiColon },
		{ "\\", sf::Keyboard::BackSlash },
		{ "/", sf::Keyboard::Slash },
		{ "\"", sf::Keyboard::Quote },
		{ "=", sf::Keyboard::Equal },
		{ "-", sf::Keyboard::Dash },
		{ "~", sf::Keyboard::Tilde },
		{ "'", sf::Keyboard::Apostrophe },

		{ "insert", sf::Keyboard::Insert },
		{ "delete", sf::Keyboard::Delete },
		{ "pause", sf::Keyboard::Pause },
		{ "home", sf::Keyboard::Home },
		{ "page_up", sf::Keyboard::PageUp },
		{ "page_down", sf::Keyboard::PageDown },
		{ "end", sf::Keyboard::End },
		{ "add", sf::Keyboard::Add },
		{ "substract", sf::Keyboard::Subtract },
		{ "divide", sf::Keyboard::Divide },
		{ "multiply", sf::Keyboard::Multiply },

		{ "f1", sf::Keyboard::F1 },
		{ "f2", sf::Keyboard::F2 },
		{ "f3", sf::Keyboard::F3 },
		{ "f4", sf::Keyboard::F4 },
		{ "f5", sf::Keyboard::F5 },
		{ "f6", sf::Keyboard::F6 },
		{ "f7", sf::Keyboard::F7 },
		{ "f8", sf::Keyboard::F8 },
		{ "f9", sf::Keyboard::F9 },
		{ "f10", sf::Keyboard::F10 },
		{ "f11", sf::Keyboard::F11 },
		{ "f12", sf::Keyboard::F12 }
	};

	std::map<std::string, sf::Mouse::Button> realMouseMap = { // Supported mouse buttons
		{ "mouse_left", sf::Mouse::Left },
		{ "mouse_right", sf::Mouse::Right },
		{ "mouse_wheel", sf::Mouse::Middle }
	};

	std::map<std::string, Key> virtualKeysMap = { // Virtual key commands
		{ "up", Key::KEY_UP },
		{ "left", Key::KEY_LEFT },
		{ "down", Key::KEY_DOWN },
		{ "right", Key::KEY_RIGHT },
		{ "accel", Key::KEY_ACCEL },
		{ "space", Key::KEY_SPACE },
		{ "escape", Key::KEY_ESCAPE },
		{ "enter", Key::KEY_ENTER }
	};

	std::map<std::string, MouseButton> virtuallMouseMap = { // Virtual mouse button commands
		{ "mouse_left", MouseButton::MOUSE_LMB },
		{ "mouse_right", MouseButton::MOUSE_RMB },
		{ "mouse_wheel", MouseButton::MOUSE_WHEEL }
	};

	sf::Keyboard::Key keys[Key::NUMBER_KEYS];
	sf::Mouse::Button mice[MouseButton::NUMBER_MOUSE_BUTTONS];

	for (auto& key : keys) key = sf::Keyboard::KeyCount;
	for (auto& mouse : mice) mouse = sf::Mouse::ButtonCount;

	// The actual json processing is here
	for (const auto& [key, val] : value.asObject()) {
		if (val.isNull()) {
			continue;
		}

		if (!val.isString()) {
			io::Logger::logError("Invalid key bindings file: a string expected as a value of a binding, got: " + val.toString());
			return;
		}

		if (virtualKeysMap.contains(key)) {
			Key binding = virtualKeysMap[key];
			if (keys[binding] != sf::Keyboard::KeyCount) {
				io::Logger::logError("Invalid key bindings file: binding duplicate: " + key);
				return;
			}

			if (!realKeysMap.contains(val.asString())) {
				io::Logger::logError("Invalid key bindings file: no such real key: " + val.asString());
				return;
			}

			keys[binding] = realKeysMap[val.asString()];
		} else if (virtuallMouseMap.contains(key)) {
			MouseButton binding = virtuallMouseMap[key];
			if (mice[binding] != sf::Mouse::ButtonCount) {
				io::Logger::logError("Invalid key bindings file: mouse binding duplicate: " + key);
				return;
			}

			if (!realMouseMap.contains(val.asString())) {
				io::Logger::logError("Invalid key bindings file: no such real mouse key: " + val.asString());
				return;
			}

			mice[binding] = realMouseMap[val.asString()];
		}
	}

	m_bindings.updateBindings(keys, mice);
}
