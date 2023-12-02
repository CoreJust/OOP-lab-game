// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "AmbienceId.h"

std::string_view audio::AmbienceId::toString() const {
	static std::string s_ambienceIdNames[] {
		"MENU_MAIN",

		"WORLD_BASIC",
		"WORLD_MAZE",
		"WORLD_SANCTUARY",

		"NUMBER_AMBIENCE_IDS"
	};

	assert(m_value < std::size(s_ambienceIdNames));

	return s_ambienceIdNames[m_value];
}
