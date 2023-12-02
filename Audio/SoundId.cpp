// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "SoundId.h"

std::string_view audio::SoundId::toString() const {
	static std::string s_soundIdNames[] {
		"SOUND_CLICK",

		"SOUND_POISONING",

		"SOUND_TELEPORTATION",
		"SOUND_SAINT_SPRINGS_BUFF",

		"SOUND_HIT",
		"SOUND_SHOCK",
		"SOUND_EVIL_SPIRIT_EXPLOSION",

		"NUMBER_SOUND_IDS"
	};

	assert(m_value < std::size(s_soundIdNames));

	return s_soundIdNames[m_value];
}
