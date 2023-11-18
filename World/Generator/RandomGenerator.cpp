// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RandomGenerator.h"
#include "Utils/Random.h"

void RandomGenerator::generateInitial() {
	utils::Random random;

	const math::Vector2i size = m_pWorld.getSize();
	const math::Recti genRect { -size + 1, size - 1 };
	for (const math::Vector2i& pos : genRect) {
		Tile& tile = m_pWorld.atMutBackground(pos);
		Tile& tileFront = m_pWorld.atMutForeground(pos);

		tileFront = Tile(TileId::EMPTINESS);
		tile = random.random(0, 2) < 1 ? Tile(TileId::STONE_WALL) : Tile(TileId::STONE_FLOOR);
	}
}

void RandomGenerator::generate() {
	// TODO: mull over there
}
