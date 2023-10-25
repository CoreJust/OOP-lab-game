// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "WorldLevelId.h"
#include "Generator/WorldGenerationMaster.h"

void WorldLevelId::loadGenerationSettingsTo(WorldGenerationMaster& generationMaster) const {
	constexpr size_t DEFAULT_SEED = 1;

	switch (m_id) {
	case BASIC_LEVEL: {
		generationMaster.pushInitialGenerator(GenerationSettings(
			DEFAULT_SEED,
			GenerationSettings::NOISE_PERLIN_BASIC,
			GenerationSettings::NoiseGenerationSettings { .octaves = 4, .frequency = 0.1f, .persistance = 0.5f }
		));

		generationMaster.pushGenerator(GenerationSettings(
			DEFAULT_SEED,
			GenerationSettings::POSTGEN_PASSAGE_CREATOR,
			GenerationSettings::PostGenerationSettings { }
		));
	} break;
	case SANCTUARY_LEVEL: {
		generationMaster.pushInitialGenerator(GenerationSettings(
			DEFAULT_SEED,
			GenerationSettings::TEMPLATE_GENERATOR,
			GenerationSettings::TemplateGenerationSettings{ .id = SANCTUARY_LEVEL, .data = 0 }
		));
	} break;
	default: break;
	}
}

math::Vector2i WorldLevelId::getWorldSize() const noexcept {
	switch (m_id) {
		case BASIC_LEVEL: return math::Vector2i(40, 40);
		case SANCTUARY_LEVEL: return math::Vector2i(6, 6);
	default: return math::Vector2i();
	}
}

std::string WorldLevelId::toString() const {
	static std::string s_worldLevelIdNames[] {
		"BASIC_WORLD",
		"SANCTUARY_WORLD",

		"NUMBER_WORLD_LEVEL_IDS"
	};

	assert(m_id < std::size(s_worldLevelIdNames));

	return s_worldLevelIdNames[m_id];
}