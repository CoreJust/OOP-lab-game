// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "Math/Vector.h"
#include "Texture.h"

// Contains a pack of textures
class TextureAtlas {
private:
	sf::Texture m_texture;

public:
	TextureAtlas() = default;
	TextureAtlas(const std::string& fileName);

	void loadFrom(const std::string& fileName);

	void loadToSprite(sf::Sprite& sprite, math::Vector2u pos) const;
	Texture getTexture(const math::Vector2u& pos) const;

	math::Vector2u getSize() const;
};