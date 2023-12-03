// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityId.h"

#include <cassert>
#include "GlobalSettings.h"

const EntityStats& EntityId::getEntityStats() const {
	static EntityStats s_entityIdStats[4][EntityId::NUMBER_ENTITY_IDS] {
		{ // Easy
			EntityStats{.maxHealth = 2000, .defence = 50, .power = 35, .speed = 3.5f,	.agility = 6, .hitbox = 0.26f }, // Player
			EntityStats{.maxHealth = 2000, .defence = 0,  .power = 15, .speed = 2.8f,	.agility = 3, .hitbox = 0.26f }, // Ghost
			EntityStats{.maxHealth = 100,  .defence = 0,  .power = 0,  .speed = 1,		.agility = 2, .hitbox = 0.125f },// Evil spirit
			EntityStats{.maxHealth = 3000, .defence = 15, .power = 30, .speed = 2.5f,	.agility = 4, .hitbox = 0.26f }, // Lost in maze
			EntityStats{.maxHealth = 1000, .defence = 5,  .power = 10, .speed = 0,		.agility = 1, .hitbox = 0.3f }   // Venomous plant
		}, { // Normal
			EntityStats{.maxHealth = 1200, .defence = 15, .power = 35, .speed = 3.2f,	.agility = 6, .hitbox = 0.26f }, // Player
			EntityStats{.maxHealth = 4000, .defence = 0,  .power = 15, .speed = 3,		.agility = 4, .hitbox = 0.26f }, // Ghost
			EntityStats{.maxHealth = 100,  .defence = 0,  .power = 0,  .speed = 1,		.agility = 2, .hitbox = 0.125f },// Evil spirit
			EntityStats{.maxHealth = 4000, .defence = 15, .power = 30, .speed = 2.5f,	.agility = 5, .hitbox = 0.26f }, // Lost in maze
			EntityStats{.maxHealth = 1100, .defence = 5,  .power = 10, .speed = 0,		.agility = 1, .hitbox = 0.3f }   // Venomous plant
		}, { // Hard
			EntityStats{.maxHealth = 1000, .defence = 10, .power = 35, .speed = 3,		.agility = 6, .hitbox = 0.26f }, // Player
			EntityStats{.maxHealth = 5000, .defence = 0,  .power = 15, .speed = 3,		.agility = 4, .hitbox = 0.26f }, // Ghost
			EntityStats{.maxHealth = 100,  .defence = 0,  .power = 0,  .speed = 1,		.agility = 2, .hitbox = 0.125f },// Evil spirit
			EntityStats{.maxHealth = 6000, .defence = 15, .power = 30, .speed = 2.5f,	.agility = 5, .hitbox = 0.26f }, // Lost in maze
			EntityStats{.maxHealth = 1100, .defence = 5,  .power = 10, .speed = 0,		.agility = 1, .hitbox = 0.3f }   // Venomous plant
		}, { // Extreme
			EntityStats{.maxHealth = 600,  .defence = 5,  .power = 35, .speed = 3,		.agility = 6, .hitbox = 0.26f }, // Player
			EntityStats{.maxHealth = 8000, .defence = 20, .power = 17, .speed = 3,		.agility = 5, .hitbox = 0.26f }, // Ghost
			EntityStats{.maxHealth = 120,  .defence = 10, .power = 0,  .speed = 1.5f,	.agility = 2, .hitbox = 0.125f },// Evil spirit
			EntityStats{.maxHealth = 9000, .defence = 15, .power = 35, .speed = 2.5f,	.agility = 5, .hitbox = 0.26f }, // Lost in maze
			EntityStats{.maxHealth = 1500, .defence = 10, .power = 12, .speed = 0,		.agility = 2, .hitbox = 0.3f }   // Venomous plant
		}
	};

	assert(m_value < std::size(s_entityIdStats));

	return s_entityIdStats[GlobalSettings::get().getDifficulty()][m_value];
}

const model::DynamicModelDescription& EntityId::getDynamicModelDescription() const {
	constexpr static glm::vec3 s_simpleEntitySize(0.5f, 1.25f, 0.5f);
	constexpr static glm::vec3 s_simpleEntityFrom(-s_simpleEntitySize.x / 2, 0.1f, -s_simpleEntitySize.z / 2);

	constexpr static glm::vec3 s_tinyEntitySize(0.125f, 0.25f, 0.125f);
	constexpr static glm::vec3 s_tinyEntityFrom(-s_tinyEntitySize.x / 2, 0.5f, -s_tinyEntitySize.z / 2);

	constexpr static glm::vec3 s_smallEntitySize(0.5f, 0.25f, 0.5f);
	constexpr static glm::vec3 s_smallEntityFrom(-s_smallEntitySize.x / 2, 0.f, -s_smallEntitySize.z / 2);

	static model::DynamicModelDescription s_entityIdDMDs[] = {
		model::DynamicModelDescription::makeBox(model::SceneObject{ }, s_simpleEntityFrom, s_simpleEntitySize, { 0, 0 }), // Player
		model::DynamicModelDescription::makeBox(model::SceneObject{ }, s_simpleEntityFrom, s_simpleEntitySize, { 0, 0 }), // Ghost
		model::DynamicModelDescription::makeBox(model::SceneObject{ }, s_tinyEntityFrom,   s_tinyEntitySize,   { 0, 0 }), // Evil spirit
		model::DynamicModelDescription::makeBox(model::SceneObject{ }, s_simpleEntityFrom, s_simpleEntitySize, { 0, 0 }), // Lost in maze
		model::DynamicModelDescription::makeBox(model::SceneObject{ }, s_smallEntityFrom,  s_smallEntitySize,  { 0, 0 })  // Venomous plant
	};

	assert(m_value < std::size(s_entityIdDMDs));

	return s_entityIdDMDs[m_value];
}

std::string_view EntityId::toString() const {
	// I'd like to use something like magic_enum here, but it is not OOP
	static std::string s_entityIdNames[] {
		"PLAYER",

		"GHOST",
		"EVIL_SPIRIT",
		"LOST_IN_MAZE",
		"VENOMOUS_PLANT",

		"NUMBER_ENTITY_IDS"
	};

	assert(m_value < std::size(s_entityIdNames));

	return s_entityIdNames[m_value];
}
