// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "World/World.h"
#include "GenerationSettings.h"

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