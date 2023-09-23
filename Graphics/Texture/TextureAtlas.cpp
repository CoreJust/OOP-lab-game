#include "TextureAtlas.h"

#include <cassert>

TextureAtlas::TextureAtlas(const std::string& fileName) {
	loadFrom(fileName);
}

void TextureAtlas::loadFrom(const std::string& fileName) {
	m_texture.loadFromFile(fileName);
}

void TextureAtlas::loadToSprite(sf::Sprite& sprite, utils::Vector2u pos) const {
	assert(pos.isToLeftUpFrom(getSize()));

	pos *= Texture::TEXTURE_SIZE;
	sprite = sf::Sprite(m_texture, sf::IntRect(pos.x(), pos.y(), Texture::TEXTURE_SIZE, Texture::TEXTURE_SIZE));
}

Texture TextureAtlas::getTexture(const utils::Vector2u& pos) const {
	sf::Sprite sprite;

	loadToSprite(sprite, pos);
	return Texture(std::move(sprite));
}

utils::Vector2u TextureAtlas::getSize() const {
	return utils::Vector2u(m_texture.getSize().x / Texture::TEXTURE_SIZE, m_texture.getSize().y / Texture::TEXTURE_SIZE);
}
