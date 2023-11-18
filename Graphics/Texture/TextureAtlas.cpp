// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TextureAtlas.h"

#include <cassert>

TextureAtlas::TextureAtlas(const std::string& fileName) : m_texture(fileName) { }

model::TextureCoords TextureAtlas::genTexCoordsGenerator() const {
	return model::TextureCoords(math::Vector2f{ UNIT_SIZE, UNIT_SIZE });
}

void TextureAtlas::loadFrom(const std::string& fileName) {
	if (auto result = m_texture.loadFromFile(fileName); !result.isOk()) {
		io::Logger::logError(result.error());
	}
}

void TextureAtlas::bind() {
	m_texture.bind();
}

void TextureAtlas::unbind() {
	m_texture.unbind();
}

const Texture& TextureAtlas::getTexture() const {
	return m_texture;
}

math::Vector2u TextureAtlas::getSize() const {
	return math::Vector2u(ATLAS_SIZE);
}
