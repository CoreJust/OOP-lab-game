// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "AnimationId.h"

#include <cassert>

std::string AnimationId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_animationIdNames[] {
		"PLAYER",

		"NUMBER_ANIMATION_IDS"
	};

	assert(m_id < std::size(s_animationIdNames));

	return s_animationIdNames[m_id];
}

std::string AnimationId::getResourceLocation() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_animationIdLocs[] {
		"player",

		""
	};

	assert(m_id < std::size(s_animationIdLocs) && m_id != NUMBER_ANIMATION_IDS);

	return s_animationIdLocs[m_id];
}
