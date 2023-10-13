// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TextureAtlas.h"

#include <cassert>

TextureAtlas::TextureAtlas(const std::string& fileName) {
	loadFrom(fileName);
}

void TextureAtlas::loadFrom(const std::string& fileName) {
	m_texture.loadFromFile(fileName);
}

void TextureAtlas::loadToSprite(sf::Sprite& sprite, math::Vector2u pos) const {
	assert(pos.isToUpLeftFrom(getSize()));

	pos *= Texture::TEXTURE_SIZE;
	sprite = sf::Sprite(m_texture, sf::IntRect(pos.x(), pos.y(), Texture::TEXTURE_SIZE, Texture::TEXTURE_SIZE));
}

Texture TextureAtlas::getTexture(const math::Vector2u& pos) const {
	sf::Sprite sprite;

	loadToSprite(sprite, pos);
	return Texture(std::move(sprite));
}

math::Vector2u TextureAtlas::getSize() const {
	return math::Vector2u(m_texture.getSize().x / Texture::TEXTURE_SIZE, m_texture.getSize().y / Texture::TEXTURE_SIZE);
}
