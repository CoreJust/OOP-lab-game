// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "MazeGenerator.h"
#include <algorithm>

void MazeGenerator::generateInitial() {
	if (m_sets.flags == GenerationSettings::MAZE_PERFECT) {
		recursiveBacktracker();
	} else if (m_sets.flags == GenerationSettings::MAZE_BRAID) {
		recursiveBacktracker();
		makeImperfect();
	}
}

void MazeGenerator::generate() {
	assert(false && "Cannot continue generation with maze");
}

void MazeGenerator::recursiveBacktracker() {
	auto getPossibleDirection = [this](const math::Vector2i& pos) -> math::DirectionFlag {
		auto mazeRect = math::Recti(-m_pWorld.getSize() + 1, m_pWorld.getSize() - 1);
		uint8_t result = math::NONE;

		if (mazeRect.contains(pos.up(1)) && m_pWorld.isObstacleAt(pos.up(2)) 
			&& m_pWorld.isObstacleAt(pos.up(2).left(1)) && m_pWorld.isObstacleAt(pos.up(2).right(1))) {
			result |= math::UP;
		} if (mazeRect.contains(pos.down(1)) && m_pWorld.isObstacleAt(pos.down(2))
			 && m_pWorld.isObstacleAt(pos.down(2).left(1)) && m_pWorld.isObstacleAt(pos.down(2).right(1))) {
			result |= math::DOWN;
		} if (mazeRect.contains(pos.right(1)) && m_pWorld.isObstacleAt(pos.right(2))
			 && m_pWorld.isObstacleAt(pos.right(2).up(1)) && m_pWorld.isObstacleAt(pos.right(2).down(1))) {
			result |= math::RIGHT;
		} if (mazeRect.contains(pos.left(1)) && m_pWorld.isObstacleAt(pos.left(2))
			  && m_pWorld.isObstacleAt(pos.left(2).up(1)) && m_pWorld.isObstacleAt(pos.left(2).down(1))) {
			result |= math::LEFT;
		}

		return math::DirectionFlag(result);
	};

	auto pickDirection = [this](uint8_t& dirs, math::DirectionFlag lastDir) -> math::DirectionFlag {
		if (dirs == math::NONE) {
			return math::NONE;
		}

		const uint8_t upSize = dirs & 1;
		const uint8_t upDownSize = upSize + ((dirs & 2) >> 1);
		const uint8_t upDownRightSize = upDownSize + ((dirs & 4) >> 2);
		uint8_t dirsSize = upDownRightSize + ((dirs & 8) >> 3);
		uint8_t preserveDirs = dirsSize + (dirs & lastDir ? m_sets.mazeSets.straightness : 0);
		uint8_t val = m_rand.random(0, preserveDirs - 1);

		if (val < upSize) {
			dirs ^= math::UP;
			return math::UP;
		} else if (val < upDownSize) {
			return math::DOWN;
		} else if (val < upDownRightSize) {
			return math::RIGHT;
		} else if (val < dirsSize) {
			return math::LEFT;
		} else {
			return lastDir;
		}
	};

	m_pWorld.fillArea({ -m_pWorld.getSize(), m_pWorld.getSize() }, false, TileId::STONE_WALL);
	m_pWorld.atMutBackground({ 0, 0 }) = Tile(TileId::STONE_FLOOR);
		
	math::Vector2i pos = { 0, 0 };
	uint8_t dirs = getPossibleDirection(pos);
	std::vector<math::DirectionFlag> dirsStack = { math::NONE };

	while (true) {
		// Delving deeper
		if (auto newDir = pickDirection(dirs, dirsStack.back()); newDir) {
			dirsStack.push_back(newDir);

			auto offset = math::Direction<int32_t>::getDirectionVector(newDir);
			pos += offset;
			m_pWorld.atMutBackground(pos) = Tile(TileId::STONE_FLOOR);
			pos += offset;
			m_pWorld.atMutBackground(pos) = Tile(TileId::STONE_FLOOR);

			dirs = getPossibleDirection(pos);
		} else { // Unrolling the stack
			if (dirsStack.size() == 1) {
				break; // Maze done
			}

			pos -= math::Direction<int32_t>::getDirectionVector(dirsStack.back()) * 2;
			dirsStack.pop_back();

			dirs = getPossibleDirection(pos);
		}
	}
}

void MazeGenerator::makeImperfect() {
	const math::Vector2i size = m_pWorld.getSize();
	for (int32_t x = -size.x() + 3; x < size.x() - 3; x += 2) {
		for (int32_t y = -size.y() + 3; y < size.y() - 3; y += 2) {

			const uint8_t vns = 0xf & ~static_cast<uint8_t>(m_pWorld.getVNSFor({ x, y }));
			if (std::has_single_bit(static_cast<uint8_t>(vns))) {

				const float chance = m_rand.random(0, 10'000) / 10000.f;
				if (chance < m_sets.mazeSets.imperfectionChance) {
					const math::Vector2i offset = -math::Direction<int32_t>::getDirectionVector(vns);
					m_pWorld.atMut(false, offset + math::Vector2i(x, y)) = Tile(TileId::STONE_FLOOR);
				}
			}
		}
	}
}
