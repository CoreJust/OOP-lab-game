// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ResourceManager.h"

#include <cassert>

#include "GlobalSettings.h"

ResourceManager::ResourceManager() {
	m_textures.resize(static_cast<uint32_t>(TextureId::NUMBER_TEXTURE_IDS));
	m_animations.resize(static_cast<uint32_t>(AnimationId::NUMBER_ANIMATION_IDS));
}

TextureAtlas& ResourceManager::getOrLoadTextureAtlas(const std::string& name) {
	if (!m_atlases.contains(name)) {
		m_atlases[name] = std::make_unique<TextureAtlas>(GlobalSettings::get().getTexturesLocation() + name + ".png");
	}

	return *m_atlases[name];
}

void ResourceManager::registerTexture(const TextureId texId, Texture texture) {
	uint32_t id = static_cast<uint32_t>(texId);
	assert(id < static_cast<uint32_t>(TextureId::NUMBER_TEXTURE_IDS));

	m_textures[id] = std::move(texture);
}

void ResourceManager::registerAnimation(const AnimationId animId, AnimationData animation) {
	uint32_t id = static_cast<uint32_t>(animId);
	assert(id < static_cast<uint32_t>(AnimationId::NUMBER_ANIMATION_IDS));

	m_animations[id] = std::move(animation);
}

Texture& ResourceManager::getTexture(const TextureId texId) {
	uint32_t id = static_cast<uint32_t>(texId);
	assert(id < m_textures.size());

	return m_textures[id];
}

AnimationData& ResourceManager::getAnimationData(const AnimationId animId) {
	uint32_t id = static_cast<uint32_t>(animId);
	assert(id < m_animations.size());

	return m_animations[id];
}
