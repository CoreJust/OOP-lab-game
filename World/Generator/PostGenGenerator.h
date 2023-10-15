// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"
#include <vector>

class PostGenGenerator final : public WorldGenerator {
private:
	GenerationSettings m_sets;

public:
	inline PostGenGenerator(World& pWorld, GenerationSettings sets) : WorldGenerator(pWorld), m_sets(std::move(sets)) {
		assert(m_sets.isPostGen());
	}

	void generateInitial() override;
	void generate() override;

private:
	void createPassages(); // Implementation of POSTGEN_PASSAGE_CREATOR

	uint32_t clusterWorldCavities(std::vector<int32_t>& map); // Clusters the world's passable areas and counts them, returns the count
	void makePassages(std::vector<int32_t>& map, uint32_t clusterCount); // Marks walls to be removed
};