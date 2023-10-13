// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RenderMaster.h"

#include "Graphics/Texture/ResourceRegisterer.h"

RenderMaster::RenderMaster() 
	: m_tileRenderer(m_resources) {
	ResourceRegisterer registerer(m_resources);
	registerer.registerAll();
}

void RenderMaster::drawEntity(std::reference_wrapper<Animation> animation, const math::Vector2f& position) {
	m_entityRenderer.addAnimation(animation, position);
}

void RenderMaster::drawTile(const TileId id, const bool isForeground, const math::Vector2f& position) {
	m_tileRenderer.addTile(isForeground, position, id);
}

void RenderMaster::render(sf::RenderWindow& window, Camera& camera) {
	window.clear(sf::Color::Black);

	m_tileRenderer.render(window, camera);
	m_entityRenderer.render(window, camera);
	m_guiRenderer.render(window, camera);
}

GameGUIRenderer& RenderMaster::getGameGuiRenderer() noexcept {
	return m_guiRenderer;
}

ResourceManager& RenderMaster::getResources() noexcept {
	return m_resources;
}
