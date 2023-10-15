// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ResourceRegisterer.h"

#include "AnimationId.h"
#include "TextureId.h"

ResourceRegisterer::ResourceRegisterer(ResourceManager& resManager)
	: m_resManager(resManager) {
}

void ResourceRegisterer::registerAll() {
	for (id_t id = 1; id < TextureId::NUMBER_TEXTURE_IDS; id++) {
		registerTexture(TextureId::Value(id));
	}

	registerAnimation(AnimationId::PLAYER, { 4, 4, 4, 4 }, 0.2f);
}

void ResourceRegisterer::registerTexture(const TextureId texId) {
	TextureAtlas& atlas = m_resManager.getOrLoadTextureAtlas(texId.getResourceLocation());
	m_resManager.registerTexture(texId, atlas.getTexture(math::Vector2u(0, 0)));
}

void ResourceRegisterer::registerAnimation(const AnimationId animId, const std::vector<uint32_t>& animationLegths, const float slideDuration) {
	TextureAtlas& atlas = m_resManager.getOrLoadTextureAtlas(animId.getResourceLocation());
	m_resManager.registerAnimation(animId, AnimationData(atlas, animationLegths, slideDuration));
}
