// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Graphics/Texture/ResourceManager.h"
#include "Graphics/Camera.h"
#include "EntityRenderer.h"
#include "TileRenderer.h"
#include "GameGUIRenderer.h"

// Used to render all the graphics but GUI
class RenderMaster final {
private:
	ResourceManager m_resources;

	EntityRenderer m_entityRenderer;
	TileRenderer m_tileRenderer;
	GameGUIRenderer m_guiRenderer;

public:
	RenderMaster();

	void drawEntity(std::reference_wrapper<Animation> animation, const math::Vector2f& position);
	void drawTile(const TileId id, const bool isForeground, const math::Vector2f& position);

	void render(sf::RenderWindow& window, Camera& camera);

	GameGUIRenderer& getGameGuiRenderer() noexcept;
	ResourceManager& getResources() noexcept;
};