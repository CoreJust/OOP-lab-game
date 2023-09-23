#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Utils/Vector.h"

// Contains a single texture of something
class Texture {
protected:
	sf::Sprite m_sprite;

public:
	// A single texture of a tile is 32x32 pixels
	constexpr static uint32_t TEXTURE_SIZE = 32;

public:
	Texture() = default;
	Texture(sf::Sprite sprite);

	void render(sf::RenderWindow& window, utils::Vector2f pos);
};