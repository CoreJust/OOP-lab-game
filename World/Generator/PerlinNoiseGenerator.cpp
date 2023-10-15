// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PerlinNoiseGenerator.h"
#include "IO/Logger.h"
#include "Math/PerlinNoise.h"
#include "Utils/Random.h"
#include "Math/ChanceDistribution.h"

constexpr float WALL_THRESHOLD = 0.5f; // the value required for a wall to be generated
constexpr float STONE_CHANCE = 0.05f;
constexpr float SPRINGS_CHANCE = 0.01f;
constexpr float POISON_CHANCE = 0.055f;
constexpr float PORTAL_CHANCE = 0.035f;

constexpr uint32_t SPAWN_AREA_SIZE = 2;

void PerlinNoiseGenerator::generateInitial() {
	math::PerlinNoise<float> noise(m_sets.seed, m_sets.noiseSets.octaves, m_sets.noiseSets.frequency, m_sets.noiseSets.persistance, 1);
	utils::Random random;
	math::ChanceDistribution<decltype(random)::RG, TileId> chanceDist(random, TileId::STONE_FLOOR);
	chanceDist.push(STONE_CHANCE, TileId::STONE);
	chanceDist.push(SPRINGS_CHANCE, TileId::SAINT_SPRINGS);
	chanceDist.push(POISON_CHANCE, TileId::POISON_CLOUD);
	size_t portalChanceIndex = chanceDist.push(PORTAL_CHANCE, TileId::STONE_PORTAL);

	const math::Vector2i size = m_pWorld.getSize();
	uint32_t portalsCount = 0;

	const math::Recti genRect { -size + 1, size - 1 };
	for (const math::Vector2i& pos : genRect) {
		Tile& tile = m_pWorld.atMutBackground(pos);
		Tile& tileFront = m_pWorld.atMutForeground(pos);

		float value = noise.rangedOctaveNoise(float(pos.x()), float(pos.y()));

		if (pos.abs().isToUpLeftFrom({ SPAWN_AREA_SIZE, SPAWN_AREA_SIZE })) { // Generating spawn point
			tile = Tile(TileId::STONE_FLOOR);
		} else if (value < WALL_THRESHOLD) {
			TileId id = chanceDist.pick();
			if (id == TileId::STONE_PORTAL) {
				chanceDist.setChance(portalChanceIndex, PORTAL_CHANCE * (3.f / float(portalsCount++ + 3)));
			}

			if (id.isBackground()) {
				tile = Tile(id);
			} else {
				tile = Tile(TileId::STONE_FLOOR);
				tileFront = Tile(id);
			}
		} else {
			tile = Tile(TileId::STONE_WALL);
		}
	}

	// Bounds
	m_pWorld.fillArea({ -size, size.mirrorByX() }, 0, TileId::STONE_WALL);
	m_pWorld.fillArea({ -size, size.mirrorByY() }, 0, TileId::STONE_WALL);
	m_pWorld.fillArea({ size.mirrorByX(), size }, 0, TileId::STONE_WALL);
	m_pWorld.fillArea({ size.mirrorByY(), size }, 0, TileId::STONE_WALL);

	// Next level portal
	math::Vector2i nextLevelPortalPos = m_pWorld.getRandomPassableLocation();
	m_pWorld.atMut(1, nextLevelPortalPos) = Tile(TileId::NEXT_LEVEL_PORTAL);
	io::Logger::logInfo("Generated next level portal at: " + nextLevelPortalPos.toString());
}

void PerlinNoiseGenerator::generate() {
	
}
