// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Text.hpp>

#include "World/Tile/TileId.h"
#include "GameGUI.h"

/*
*	Minimap(.h/.cpp) contains a class that inherits GameGUI
*	and implements a minimap of the world.
*/

namespace gamegui {
	class Minimap final : public GameGUI {
	public:
		constexpr inline static uint32_t MINIMAP_SIZE = 17;
		constexpr inline static float MINIMAP_SCALE_BASE = 0.025f;

	private:
		sf::Image m_minimap;
		sf::Texture m_minimapTexture; // The holder for the texture

		math::Vector2i m_playerPos;

	public:
		Minimap(const math::Vector2f& pos);

		void setPlayerPos(const math::Vector2f& pos);
		void setTile(const TileId id, const math::Vector2i& pos);
		void update();
	};
}