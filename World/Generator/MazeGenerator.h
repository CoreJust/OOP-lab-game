// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"

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