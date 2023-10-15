// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TemplateGenerator.h"
#include "World/WorldLevelId.h"

void TemplateGenerator::generateInitial() {
	WorldLevelId id = WorldLevelId::Value(m_sets.templateSets.id);

	switch (id) {
		case WorldLevelId::SANCTUARY_LEVEL: generateSanctuary(); break;
	default: assert(false && "No template generation for this level"); break;
	}
}

void TemplateGenerator::generate() {
	assert(false && "Cannot modify generation with fixed template generator");
}

void TemplateGenerator::generateSanctuary() {
	const math::Vector2i size = m_pWorld.getSize();

	// Floor
	m_pWorld.fillArea({ -size, size }, 0, TileId::STONE_FLOOR);

	math::Recti worldRect { -size, size };

	m_pWorld.fillAreaBounds(worldRect, 1, TileId::STONE); // bounds
	m_pWorld.fillAreaBounds(worldRect.clip(1), 1, TileId::SAINT_SPRINGS);
	m_pWorld.fillAreaBounds(worldRect.clip(2), 0, TileId::STONE_PORTAL);

	m_pWorld.atMut(1, { 0, 0 }) = Tile(TileId::SAINT_SPRINGS);
}
