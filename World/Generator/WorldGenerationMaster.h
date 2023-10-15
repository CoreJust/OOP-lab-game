// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include "WorldGenerator.h"

/*
*	Usage:
*	Initializing with a world:
*		WorldGenerationMaster master(world);
* 
*	Pushing the initial generator - the one that would fiil in the world.
*	Note that not any generator can be initial.
*		master.pushInitialGenerator(GenerationSettings { ... });
*	
*	Pushing some consecutive generators that would modify the world.
*	Note that not any generator can be consecutive.
*	There could be no such generators.
*		master.pushGenerator(GenerationSettings { ... });
*		master.pushGenerator(GenerationSettings { ... });
*		...
* 
*	And finally we run the generation:
*		master.generate()
*/

class WorldGenerationMaster final {
private:
	World& m_pWorld;
	std::vector<std::unique_ptr<WorldGenerator>> m_generators;

public:
	WorldGenerationMaster(World& pWorld) noexcept;

	void generate(); // starts the actusl generation
	void pushInitialGenerator(GenerationSettings sets); // the first generator
	void pushGenerator(GenerationSettings sets); // (optinal) the next generators

private:
	void pushGenerator(std::unique_ptr<WorldGenerator> generator);
};