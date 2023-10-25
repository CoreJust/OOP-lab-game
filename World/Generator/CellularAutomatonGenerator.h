// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"

/*
*	CellularAutomatonGenerator(.h/.cpp) contains one of the WorldGenerators.
*
*	CellularAutomatonGenerator allows to use cellular automatons to generate a world.
*	It is the generator with the broadest set of possible generations (in terms of 
*	the general structure), since most of the other generator can be partially reproduced
*	with this generator (that wouldn't be effecient though).
*/

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