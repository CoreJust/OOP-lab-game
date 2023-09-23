#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Graphics/Texture/ResourceManager.h"
#include "Graphics/Camera.h"
#include "EntityRenderer.h"
#include "TileRenderer.h"

// Used to render all the graphics but GUI
class RenderMaster final {
private:
	ResourceManager m_resources;

	EntityRenderer m_entityRenderer;
	TileRenderer m_tileRenderer;

public:
	RenderMaster();

	void drawEntity(Animation* animation, const utils::Vector2f& position);
	void drawTile(TileId id, bool isForeground, const utils::Vector2f& position);

	void render(sf::RenderWindow& window, Camera& camera);

	ResourceManager& getResources();
};