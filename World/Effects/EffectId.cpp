// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EffectId.h"

std::string EffectId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_effectIdNames[] {
		"Acceleration",
		"Deceleration",

		"Vitality",
		"Illness",

		"Great power",
		"Powerlessness",

		"Defensive aura",
		"Defence corruption",

		"Healing",
		"Damage",

		"Immortality",
		"Spiritual form",

		"Invisibility",

		"Instaheal",
		"Instadamage",

		"Random teleportation",

		"NUMBER_EFFECT_IDS"
	};

	assert(m_id < std::size(s_effectIdNames));

	return s_effectIdNames[m_id];
}
