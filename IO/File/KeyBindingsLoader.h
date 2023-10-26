// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "IO/Json/JsonFileParser.h"
#include "IO/Input/KeyBindings.h"

/*
*	KeyBindingsLoader(.h/.cpp) contains a class that allows to load and parse
*	the key bindings from a json file.
* 
*	The path to the file is taken from the global settings.
* 
*	It is based on the parent class JsonFileLoader.
* 
*	Sample file:
*	{
*		"up": "w",
*		"left": "a",
*		"down": "s",
*		"right": "d",
*
*		"accel": "left_shift",
*		"space": "space",
*		"escape": "escape",
*		"enter": "enter"
*	}
*/

namespace io {
	class KeyBindingsLoader final : public JsonFileParser {
	private:
		KeyBindings& m_bindings;

	public:
		constexpr KeyBindingsLoader(KeyBindings& bindings) : JsonFileParser(""), m_bindings(bindings) { }

		void load();

	private:
		void loadDefaultBindings();
		void loadFromParsed(io::JsonValue value);
	};
}
