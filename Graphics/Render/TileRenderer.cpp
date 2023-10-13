// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TileRenderer.h"

TileRenderer::TileRenderer(ResourceManager& pManager)
	: m_pManager(pManager) {

}

void TileRenderer::addTile(const bool isForeground, const math::Vector2f& pos, const TileId id) {
	m_tiles[isForeground].emplace_back(TileRenderInfo { id, pos });
}

void TileRenderer::render(sf::RenderWindow& window, Camera& camera) {
	for (uint8_t layer = 0; layer <= 1; layer++) {
		for (size_t i = 0; i < m_tiles[layer].size(); i++) {
			TileRenderInfo& info = m_tiles[layer][i];
			m_pManager.getTexture(info.id.getTileTexture()).render(window, camera.getPosInView(info.pos), camera.getSingularObjectSize());
		}
	}

	m_tiles[0].clear();
	m_tiles[1].clear();
}
