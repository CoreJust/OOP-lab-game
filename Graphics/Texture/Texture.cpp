// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Texture.h"

Texture::Texture(sf::Sprite sprite)
	: m_sprite(std::move(sprite)) {

}

void Texture::render(sf::RenderWindow& window, const math::Vector2f& pos, const math::Vector2f& scale) {
	// pos *= TEXTURE_SIZE;
	m_sprite.setPosition(pos.toSfml());
	m_sprite.setScale(scale.toSfml());
	window.draw(m_sprite);
}
