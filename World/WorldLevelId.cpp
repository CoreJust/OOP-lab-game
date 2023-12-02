// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "WorldLevelId.h"
#include "Utils/Seed.h"
#include "Generator/WorldGenerationMaster.h"

void WorldLevelId::loadGenerationSettingsTo(WorldGenerationMaster& generationMaster) const {
	switch (m_value) {
	case BASIC_LEVEL: {
		generationMaster.pushInitialGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::NOISE_PERLIN_BASIC,
			GenerationSettings::NoiseGenerationSettings { .octaves = 4, .frequency = 0.1f, .persistance = 0.5f }
		));

		generationMaster.pushGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::POSTGEN_BOUNDS_CREATOR,
			GenerationSettings::PostGenerationSettings { }
		));

		generationMaster.pushGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::POSTGEN_PASSAGE_CREATOR,
			GenerationSettings::PostGenerationSettings { }
		));

		generationMaster.pushGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::POSTGEN_DECORATOR,
			GenerationSettings::PostGenerationSettings { .allowObstacles = true, .allowDangers = true, .allowPortals = true }
		));

		generationMaster.pushGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::POSTGEN_PASSAGE_CREATOR,
			GenerationSettings::PostGenerationSettings { }
		));

		generationMaster.pushGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::POSTGEN_NEXT_LEVEL_PORTAL_GENERATOR,
			GenerationSettings::PostGenerationSettings { }
		));

		generationMaster.pushEnemyGenerator({ 
			{ EntityId::VENOMOUS_PLANT, 12 },
			{ EntityId::EVIL_SPIRIT, 12 },
			{ EntityId::GHOST, 20 }
		});
	} break;
	case MAZE_LEVEL: {
		generationMaster.pushInitialGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::MAZE_BRAID,
			GenerationSettings::MazeGenerationSettings { .straightness = 2, .imperfectionChance = 0.35f }
		));

		generationMaster.pushGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::POSTGEN_DECORATOR,
			GenerationSettings::PostGenerationSettings { .allowObstacles = false, .allowDangers = false, .allowPortals = false }
		));

		generationMaster.pushGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::POSTGEN_NEXT_LEVEL_PORTAL_GENERATOR,
			GenerationSettings::PostGenerationSettings { }
		));

		generationMaster.pushEnemyGenerator({
			{ EntityId::LOST_IN_MAZE, 20 }
		});
	} break;
	case SANCTUARY_LEVEL: {
		generationMaster.pushInitialGenerator(GenerationSettings(
			utils::Seed::seed(),
			GenerationSettings::TEMPLATE_GENERATOR,
			GenerationSettings::TemplateGenerationSettings{ .id = SANCTUARY_LEVEL, .data = 0 }
		));
	} break;
	default: break;
	}
}

math::Vector2i WorldLevelId::getWorldSize() const noexcept {
	switch (m_value) {
		case BASIC_LEVEL: return math::Vector2i(40, 40);
		case MAZE_LEVEL: return math::Vector2i(21, 21);
		case SANCTUARY_LEVEL: return math::Vector2i(6, 6);
	default: return math::Vector2i();
	}
}

const std::vector<std::string>& WorldLevelId::getTutorialTexts() const noexcept {
	static std::vector<std::string> s_tutorialTexts[] = {
		{ // Basic world
			"Welcome to the OOP lab game!",
			"This is the first level of the game.",
			"You need to find the golden portal\nto go to the next level.",
			"But beware! A danger awaits you.",
			"Good luck!        "
		}, { // Maze world
			"Congratulations!",
			"You have successfully passed the first level.",
			"Now, here is a maze.",
			"You need to find the portal once again.",
			"Good luck!       "
		}, { // Sanctuary world
			"Congratulations! You have passed the game!",
			"And here is the sanctuary!",
			"Enjoy!"
		}
	};

	assert(m_value < std::size(s_tutorialTexts));

	return s_tutorialTexts[m_value];
}

std::string_view WorldLevelId::toString() const {
	static std::string s_worldLevelIdNames[] {
		"BASIC_WORLD",
		"MAZE_WORLD",
		"SANCTUARY_WORLD",

		"NUMBER_WORLD_LEVEL_IDS"
	};

	assert(m_value < std::size(s_worldLevelIdNames));

	return s_worldLevelIdNames[m_value];
}
