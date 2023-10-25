// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "World/World.h"
#include "GenerationSettings.h"

/*
*	WorldGenerator(.h/.cpp) contains a base class for all the generators.
*
*	In general, a generator takes as input reference to a world and then modifies it
*	- which is called the world generation.
* 
*	There are two kinds of generation - the initial and the sequential. The former,
*	just as the name implies, is used the first and only once, and it fills the empty world.
*	The latter is employed as much as one wants (or needs) but after the former only.
*	It allows to modify an already generated world.
*/

class WorldGenerator {
protected:
	World& m_pWorld;

protected:
	WorldGenerator(World& pWorld);

public:
	virtual ~WorldGenerator() = default;

	virtual void generateInitial() = 0; // The first (and probably only) generation
	virtual void generate() = 0; // The consecutive generations after the initial

	static std::unique_ptr<WorldGenerator> makeWorldGenerator(World& pWorld, GenerationSettings sets);
};