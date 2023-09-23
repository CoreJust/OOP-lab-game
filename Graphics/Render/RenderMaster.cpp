#include "RenderMaster.h"

#include "Graphics/Texture/ResourceRegisterer.h"

RenderMaster::RenderMaster() 
	: m_tileRenderer(&m_resources) {
	ResourceRegisterer registerer(m_resources);
	registerer.registerAll();
}

void RenderMaster::drawEntity(Animation* animation, const utils::Vector2f& position) {
	m_entityRenderer.addAnimation(animation, position);
}

void RenderMaster::drawTile(TileId id, bool isForeground, const utils::Vector2f& position) {
	m_tileRenderer.addTile(isForeground, position, id);
}

void RenderMaster::render(sf::RenderWindow& window, Camera& camera) {
	window.clear(sf::Color::Black);

	m_tileRenderer.render(window, camera);
	m_entityRenderer.render(window, camera);
}

ResourceManager& RenderMaster::getResources() {
	return m_resources;
}
