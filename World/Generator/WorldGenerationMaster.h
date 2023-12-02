// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include "WorldGenerator.h"
#include "EnemyGenerator.h"

/*
*	WorldGenerationMaster(.h/.cpp) contains a class that manages the generators.
* 
*	It can be fed with consecutive generation stages' settings and than be applied
*	to a world to generate it totally and completely - the world does not need any further
*	actions to get ready to use.
* 
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
	std::vector<EnemyGenerator> m_enemyGenerators;

public:
	WorldGenerationMaster(World& pWorld) noexcept;

	void generate(); // starts the actusl generation
	void pushInitialGenerator(GenerationSettings sets); // the first generator
	void pushGenerator(GenerationSettings sets); // (optinal) the next generators
	void pushEnemyGenerator(std::vector<std::pair<EntityId, uint32_t>> enemies, const float minDistance = 6.f);

private:
	void pushGenerator(std::unique_ptr<WorldGenerator> generator);
};