// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "WorldGenerationMaster.h"

WorldGenerationMaster::WorldGenerationMaster(World& pWorld) noexcept : m_pWorld(pWorld) { }

void WorldGenerationMaster::generate() {
	m_generators[0]->generateInitial();

	for (size_t i = 1; i < m_generators.size(); i++) {
		m_generators[i]->generate();
	}

	for (auto& eg : m_enemyGenerators) {
		eg.generate();
	}
}

void WorldGenerationMaster::pushInitialGenerator(GenerationSettings sets) {
	assert(m_generators.size() == 0);

	pushGenerator(WorldGenerator::makeWorldGenerator(m_pWorld, std::move(sets)));
}

void WorldGenerationMaster::pushGenerator(GenerationSettings sets) {
	assert(m_generators.size() != 0);

	pushGenerator(WorldGenerator::makeWorldGenerator(m_pWorld, std::move(sets)));
}

void WorldGenerationMaster::pushEnemyGenerator(std::vector<std::pair<EntityId, uint32_t>> enemies, const float minDistance) {
	m_enemyGenerators.emplace_back(m_pWorld, std::move(enemies), minDistance);
}

void WorldGenerationMaster::pushGenerator(std::unique_ptr<WorldGenerator> generator) {
	m_generators.push_back(std::move(generator));
}
