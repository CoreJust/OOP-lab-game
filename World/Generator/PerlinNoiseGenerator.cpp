// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PerlinNoiseGenerator.h"
#include "Math/PerlinNoise.h"
#include "Utils/Random.h"

constexpr float WALL_THRESHOLD = 0.5f; // the value required for a wall to be generated
constexpr float PORTAL_CHANCE = 0.035f;
constexpr float STONE_CHANCE = 0.05f;
constexpr uint32_t SPAWN_AREA_SIZE = 2;

void PerlinNoiseGenerator::generateInitial() {
	math::PerlinNoise<float> noise(m_sets.seed, m_sets.noiseSets.octaves, m_sets.noiseSets.frequency, m_sets.noiseSets.persistance, 1);
	utils::Random random;
	const math::Vector2i size = m_pWorld.getSize();
	uint32_t portalsCount = 0;

	for (int32_t y = -size.y() + 1; y < size.y(); y++) {
		for (int32_t x = -size.x() + 1; x < size.x(); x++) {
			Tile& tile = m_pWorld.atMutBackground({ x, y });

			float value = noise.rangedOctaveNoise(float(x), float(y));
			float randValue = float(random.random(0, 10'000)) / 10'000.f;

			if (abs(x) <= SPAWN_AREA_SIZE && abs(y) <= SPAWN_AREA_SIZE) { // Generating spawn point
				tile = Tile(TileId::STONE_FLOOR);
			} else if (value < WALL_THRESHOLD) {
				if (randValue > PORTAL_CHANCE * (3.f / float(portalsCount + 3))) {
					tile = Tile(TileId::STONE_FLOOR);

					if (randValue > (1 - STONE_CHANCE)) {
						m_pWorld.atMutForeground({ x, y }) = Tile(TileId::STONE);
					}
				} else {
					tile = Tile(TileId::STONE_PORTAL);
					portalsCount++;
				}
			} else {
				tile = Tile(TileId::STONE_WALL);
			}
		}
	}

	// Bounds
	m_pWorld.fillArea({ -size, size.mirrorByX() }, false, TileId::STONE_WALL);
	m_pWorld.fillArea({ -size, size.mirrorByY() }, false, TileId::STONE_WALL);
	m_pWorld.fillArea({ size.mirrorByX(), size }, false, TileId::STONE_WALL);
	m_pWorld.fillArea({ size.mirrorByY(), size }, false, TileId::STONE_WALL);
}

void PerlinNoiseGenerator::generate() {
	
}
