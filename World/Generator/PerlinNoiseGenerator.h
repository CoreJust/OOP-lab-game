// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"

/*
*	PerlinNoiseGenerator(.h/.cpp) contains one of the WorldGenerators.
*
*	PerlinNoiseGenerator provides the usage of PerlinNoise (and potentially SimplexNoise someday).
*	It can be employed for some terrain generation (or similar things).
* 
*	The general idea of the underlying principles is overlaying several interpolated white noise maps
*	with different scales and impact, thus creating a complex structure, where the first octave creates
*	the most general structure with each next one bringing in more and more details.
*/

// Generates world with Perlin noise
class PerlinNoiseGenerator final : public WorldGenerator {
private:
	GenerationSettings m_sets;

public:
	inline PerlinNoiseGenerator(World& pWorld, GenerationSettings sets) : WorldGenerator(pWorld), m_sets(std::move(sets)) {
		assert(m_sets.isNoise());
	}

	void generateInitial() override;
	void generate() override;
};