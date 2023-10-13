// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "WorldGenerator.h"
#include "RandomGenerator.h"
#include "PerlinNoiseGenerator.h"
#include "MazeGenerator.h"
#include "CellularAutomatonGenerator.h"
#include "PostGenGenerator.h"

WorldGenerator::WorldGenerator(World& pWorld) 
	: m_pWorld(pWorld) {

}

std::unique_ptr<WorldGenerator> WorldGenerator::makeWorldGenerator(World& pWorld, GenerationSettings sets) {
	if (sets.isRandom()) {
		return std::make_unique<RandomGenerator>(pWorld, std::move(sets));
	} else if (sets.isNoise()) {
		return std::make_unique<PerlinNoiseGenerator>(pWorld, std::move(sets));
	} else if (sets.isMaze()) {
		return std::make_unique<MazeGenerator>(pWorld, std::move(sets));
	} else if (sets.isCellularAutomaton()) {
		return std::make_unique<CellularAutomatonGenerator>(pWorld, std::move(sets));
	} else if (sets.isPostGen()) {
		return std::make_unique<PostGenGenerator>(pWorld, std::move(sets));
	}

	assert(false && "Unknown generation type");
}
