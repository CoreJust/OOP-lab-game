// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"

/*
*	RandomGenerator(.h/.cpp) contains one of the WorldGenerators.
*
*	RandomGenerator allows to bring in some absolute random. Its generation
*	does not represent any structure and is a kind of white noise. It can be used
*	for other generators as the initial and/or for some changes in the structured world.
*/

class RandomGenerator final : public WorldGenerator {
private:
	GenerationSettings m_sets;

public:
	inline RandomGenerator(World& pWorld, GenerationSettings sets) : WorldGenerator(pWorld), m_sets(std::move(sets)) {
		assert(m_sets.isRandom());
	}

	void generateInitial() override;
	void generate() override;
};