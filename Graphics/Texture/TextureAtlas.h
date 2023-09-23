#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "Utils/Vector.h"
#include "Texture.h"

// Contains a pack of textures
class TextureAtlas {
private:
	sf::Texture m_texture;

public:
	TextureAtlas() = default;
	TextureAtlas(const std::string& fileName);

	void loadFrom(const std::string& fileName);

	void loadToSprite(sf::Sprite& sprite, utils::Vector2u pos) const;
	Texture getTexture(const utils::Vector2u& pos) const;

	utils::Vector2u getSize() const;
};