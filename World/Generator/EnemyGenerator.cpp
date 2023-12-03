// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(World& pWorld, std::vector<std::pair<EntityId, uint32_t>> entities, const float minDistance)
	: m_pWorld(pWorld), m_entities(std::move(entities)), m_minDistance(minDistance) {
	assert(minDistance < m_pWorld.getSize().length());
}

void EnemyGenerator::generate() {
	for (auto& [id, count] : m_entities) {
		for (int32_t i = 0; i < count; i++) {
			math::Vector2i pos = m_pWorld.getRandomSuitableLocation([this](const math::Vector2i& pos) -> bool {
				return !m_pWorld.isObstacleAt(pos) && !m_pWorld.isInteractiveAt(pos) && pos.length() >= m_minDistance;
			});

			m_pWorld.spawn(id, pos.to<float>() + 0.5f);
		}
	}
}
