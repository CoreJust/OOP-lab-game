// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"

class CellularAutomatonGenerator final : public WorldGenerator {
private:
	GenerationSettings m_sets;

public:
	inline CellularAutomatonGenerator(World& pWorld, GenerationSettings sets) : WorldGenerator(pWorld), m_sets(std::move(sets)) {
		assert(m_sets.isCellularAutomaton());
	}

	void generateInitial() override;
	void generate() override;
};