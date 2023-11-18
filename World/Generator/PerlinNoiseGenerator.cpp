// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PerlinNoiseGenerator.h"
#include "IO/Logger.h"
#include "Math/PerlinNoise.h"
#include "Utils/Random.h"
#include "Math/ChanceDistribution.h"

constexpr float WALL_THRESHOLD = 0.5f; // the value required for a wall to be generated

constexpr uint32_t SPAWN_AREA_SIZE = 2;

void PerlinNoiseGenerator::generateInitial() {
	math::PerlinNoise<float> noise(m_sets.seed, m_sets.noiseSets.octaves, m_sets.noiseSets.frequency, m_sets.noiseSets.persistance, 1);
	const math::Vector2i size = m_pWorld.getSize();
	const math::Recti genRect { -size + 1, size - 1 };

	for (const math::Vector2i& pos : genRect) {
		Tile& tile = m_pWorld.atMutBackground(pos);
		Tile& tileFront = m_pWorld.atMutForeground(pos);

		float value = noise.rangedOctaveNoise(float(pos.x()), float(pos.y()));

		if (pos.abs().isToUpLeftFrom({ SPAWN_AREA_SIZE, SPAWN_AREA_SIZE })) { // Generating spawn point
			tile = Tile(TileId::STONE_FLOOR);
		} else if (value < WALL_THRESHOLD) {
			tile = Tile(TileId::STONE_FLOOR);
		} else {
			tile = Tile(TileId::STONE_WALL);
		}
	}
}

void PerlinNoiseGenerator::generate() {
	
}
