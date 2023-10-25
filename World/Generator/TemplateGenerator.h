// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "WorldGenerator.h"

/*
*	TemplateGenerator(.h/.cpp) contains one of the WorldGenerators.
*
*	TemplateGenerator allows to generate a world according to some template (or pattern)
*	that is set in stone (one can only choose between the templates offered and possibly
*	add some minor changes in accordance with the corresponding template's own interface).
* 
*	Such kind of generation is useful for some fixed structures and "scripted" levels.
*/

class TemplateGenerator final : public WorldGenerator {
private:
	GenerationSettings m_sets;

public:
	inline TemplateGenerator(World& pWorld, GenerationSettings sets) : WorldGenerator(pWorld), m_sets(std::move(sets)) {
		assert(m_sets.isTemplateGen());
	}

	void generateInitial() override;
	void generate() override;

private:
	void generateSanctuary();
};