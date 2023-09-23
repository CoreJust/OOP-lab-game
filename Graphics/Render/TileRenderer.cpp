#include "TileRenderer.h"

TileRenderer::TileRenderer(ResourceManager* pManager)
	: m_pManager(pManager) {

}

void TileRenderer::addTile(bool isForeground, const utils::Vector2f& pos, TileId id) {
	m_tiles[isForeground].emplace_back(TileRenderInfo { id, pos });
}

void TileRenderer::render(sf::RenderWindow& window, Camera& camera) {
	for (int layer = 0; layer <= 1; layer++) {
		for (size_t i = 0; i < m_tiles[layer].size(); i++) {
			TileRenderInfo& info = m_tiles[layer][i];
			m_pManager->getTexture(info.id.getTileTexture())->render(window, camera.getPosInView(info.pos));
		}
	}

	m_tiles[0].clear();
	m_tiles[1].clear();
}
