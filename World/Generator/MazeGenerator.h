// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"
#include "Utils/Random.h"
#include "Utils/Seed.h"

/*
*	MazeGenerator(.h/.cpp) contains one of the WorldGenerators.
*
*	MazeGenerator does just what wou would expect it to do implies
*	- generates mazes (or would do so).
*/

class MazeGenerator final : public WorldGenerator {
private:
	using Path = std::vector<math::Vector2i>;

private:
	GenerationSettings m_sets;
	utils::Random<> m_rand;

public:
	inline MazeGenerator(World& pWorld, GenerationSettings sets)
		: WorldGenerator(pWorld), m_sets(std::move(sets)) {
		assert(m_sets.isMaze());

		m_rand.setSeed(sets.seed);
	}

	void generateInitial() override;
	void generate() override;

private:
	void recursiveBacktracker();
	void makeImperfect();
};