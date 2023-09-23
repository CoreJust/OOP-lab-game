#include "Texture.h"

Texture::Texture(sf::Sprite sprite)
	: m_sprite(std::move(sprite)) {

}

void Texture::render(sf::RenderWindow& window, utils::Vector2f pos) {
	pos *= TEXTURE_SIZE;
	m_sprite.setPosition(pos.x(), -pos.y());
	window.draw(m_sprite);
}
