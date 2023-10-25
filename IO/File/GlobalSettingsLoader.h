// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "IO/Json/JsonFileParser.h"
#include "GlobalSettings.h"

/*
*	GlobalSettingsLoader(.h/.cpp) contains a class that allows to parse a json
*	file that contains settings.
* 
*	The settings are expected to be contained in the file global_sets.json.
*	The file must be located in the same directory with the executable file.
* 
*	It is based on the parent class JsonFileLoader.
* 
*	Sample settings file:
*	{
*		"resources_location": "res/",
*		"font": "Visitor_Rus",
*		"render_distance": 12,
*		"update_distance": 15,
*		"input_mode": "keyboard_and_mouse",
*		"input_file": "input_save",
*		"save_input": true,
*		"log_input": false,
*		"log_delta_time": false,
*		"log_settings": true,
*		"log_entities_pos": false,
*		"log_entities_effects": false
*	}
*/

namespace io {
	class GlobalSettingsLoader final : public JsonFileParser {
	private:
		GlobalSettings& m_sets;

	public:
		constexpr GlobalSettingsLoader(GlobalSettings& sets) : JsonFileParser(""), m_sets(sets) { }

		void load();

	private:
		void loadFromParsed(io::JsonValue value);
	};
}