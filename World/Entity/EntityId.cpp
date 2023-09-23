#include "EntityId.h"

#include <cassert>

const EntityStats& EntityId::getEntityStats() const {
	static EntityStats s_entityIdStats[] {
		EntityStats(1000, 0, 20, 2, 0.2f)
	};

	assert(m_id < std::size(s_entityIdStats));

	return s_entityIdStats[m_id];
}

std::string EntityId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_entityIdNames[] {
		"PLAYER",

		"NUMBER_ENTITY_IDS"
	};

	assert(m_id < std::size(s_entityIdNames));

	return s_entityIdNames[m_id];
}
