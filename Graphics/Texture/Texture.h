// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Math/Vector.h"

// Contains a single texture of something
class Texture {
protected:
	sf::Sprite m_sprite;

public:
	// A single texture of a tile is 32x32 pixels - the standard used by the project
	constexpr static uint32_t TEXTURE_SIZE = 32;

public:
	Texture() = default;
	Texture(sf::Sprite sprite);

	void render(sf::RenderWindow& window, const math::Vector2f& pos, const math::Vector2f& scale = { 1, 1 });
};