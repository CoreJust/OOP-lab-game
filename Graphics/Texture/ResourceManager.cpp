// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ResourceManager.h"
#include <cassert>

#include "GlobalSettings.h"

TextureAtlas& ResourceManager::getTextureAtlas() {
	assert(m_atlas);

	return *m_atlas;
}

Texture& ResourceManager::getEntityTexture(const EntityId id) {
	assert(m_entityTextures[id]);

	return *m_entityTextures[id];
}

void ResourceManager::loadTextureAtlas() {
	assert(!m_atlas);

	m_atlas = std::make_unique<TextureAtlas>(GlobalSettings::get().getTexturesLocation() + "texture_atlas.png");
}

void ResourceManager::loadEntityTexture(const EntityId id, const std::string& fileName) {
	m_entityTextures[id] = std::make_unique<Texture>(GlobalSettings::get().getTexturesLocation() + fileName + ".png");
}
