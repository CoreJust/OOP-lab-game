// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TileRenderer.h"

TileRenderer::TileRenderer(ResourceManager& pManager)
	: m_pManager(pManager), m_shader() {
	m_models.reserve(TileId::NUMBER_TILE_IDS);

	for (id_t id = 0; id < TileId::NUMBER_TILE_IDS; id++) {
		TileId tid { TileId::Value(id) };
		if (tid.getCategory() == TileCategory::WALL) {
			std::vector<model::TileModel> variants;
			variants.reserve(math::DirectionFlag::ALL_DIRECTIONS);

			for (uint32_t d = 0; d <= math::DirectionFlag::ALL_DIRECTIONS; d++) {
				variants.emplace_back(tid, math::DirectionFlag(d));
			}

			m_models.emplace_back(std::move(variants));
		} else { // plain model
			std::vector<model::TileModel> variants;
			variants.emplace_back(tid);
			m_models.emplace_back(std::move(variants));
		}
	}
}

void TileRenderer::addTile(const math::Vector2f& pos, const TileId id) {
	m_tiles.emplace_back(TileRenderInfo { .id = id, .pos = pos, .hasVNS = false });
}

void TileRenderer::addTile(const math::Vector2f& pos, const TileId id, const math::DirectionFlag VNS) {
	m_tiles.emplace_back(TileRenderInfo { .id = id, .pos = pos, .VNSurroundings = VNS, .hasVNS = true });
}

void TileRenderer::render(sf::RenderWindow& window, Camera& camera) {
	auto& atlas = m_pManager.getTextureAtlas();

	atlas.bind();
	m_shader.bind();
	m_shader.loadDefaultFogPower();
	m_shader.setPlayerPos(camera.getPos());
	m_shader.setProjViewMatrix(camera.genProjViewMatrix());

	for (auto& info : m_tiles) {
		model::TileModel& model = m_models[info.id].variants[info.hasVNS ? info.VNSurroundings : 0];
		model.sceneObject().pos.x = info.pos.x();
		model.sceneObject().pos.z = info.pos.y();
		model.render(m_shader);
	}

	m_shader.unbind();
	atlas.unbind();

	m_tiles.clear();
}
