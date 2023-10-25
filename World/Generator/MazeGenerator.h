// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"

/*
*	MazeGenerator(.h/.cpp) contains one of the WorldGenerators.
*
*	MazeGenerator does just what wou would expect it to do implies
*	- generates mazes (or would do so).
*/

class MazeGenerator final : public WorldGenerator {
private:
	GenerationSettings m_sets;

public:
	inline MazeGenerator(World& pWorld, GenerationSettings sets) : WorldGenerator(pWorld), m_sets(std::move(sets)) {
		assert(m_sets.isMaze());
	}

	void generateInitial() override;
	void generate() override;
};