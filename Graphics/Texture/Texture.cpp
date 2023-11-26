// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Texture.h"
#include <SFML/Graphics/Texture.hpp>

#include "IO/Logger/Logger.h"

Texture::Texture(const std::string& filePath) : m_textureID(0) {
	if (auto result = loadFromFile(filePath); !result.isOk()) {
		io::Logger::error("Texture: " + result.error());
	}
}

Texture::~Texture() {
	if (m_textureID) {
		glDeleteTextures(1, &m_textureID);
		m_textureID = 0;
	}
}

utils::Result<utils::Void> Texture::loadFromFile(const std::string& filePath) {
	sf::Image image;
	if (!image.loadFromFile(filePath)) {
		return utils::Failure("Failed to load from file: " + filePath);
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	setupForOpenGL();
	unbind();

	return utils::Success();
}

void Texture::setupForOpenGL() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	auto aniso = 16.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::setTextureBlock(GLenum block) {
	glActiveTexture(block);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
