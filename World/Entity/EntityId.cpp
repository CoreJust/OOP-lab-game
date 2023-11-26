// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityId.h"

#include <cassert>

const EntityStats& EntityId::getEntityStats() const {
	static EntityStats s_entityIdStats[] {
		EntityStats{ .maxHealth = 1000, .defence = 0, .power = 20, .speed = 3, .hitbox = 0.26f }, // Player
	};

	assert(m_value < std::size(s_entityIdStats));

	return s_entityIdStats[m_value];
}

const model::DynamicModelDescription& EntityId::getDynamicModelDescription() const {
	constexpr static glm::vec3 s_simpleEntitySize(0.5f, 1.25f, 0.5f);
	constexpr static glm::vec3 s_simpleEntityFrom(-s_simpleEntitySize.x / 2, 0.1f, -s_simpleEntitySize.z / 2);

	static model::DynamicModelDescription s_entityIdDMDs[] = {
		model::DynamicModelDescription::makeBox(model::SceneObject{ }, s_simpleEntityFrom, s_simpleEntitySize, { 0, 0 }) // Player
	};

	assert(m_id < std::size(s_entityIdDMDs));

	return s_entityIdDMDs[m_value];
}

std::string_view EntityId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_entityIdNames[] {
		"PLAYER",

		"NUMBER_ENTITY_IDS"
	};

	assert(m_value < std::size(s_entityIdNames));

	return s_entityIdNames[m_value];
}
