#include "ResourceRegisterer.h"

#include "AnimationId.h"
#include "TextureId.h"

ResourceRegisterer::ResourceRegisterer(ResourceManager& resManager)
	: m_resManager(resManager) {
}

void ResourceRegisterer::registerAll() {
	registerTexture(TextureId::STONE_FLOOR);
	registerTexture(TextureId::STONE_WALL);

	registerAnimation(AnimationId::PLAYER, { 4, 4, 4, 4 }, 0.2f);
}

void ResourceRegisterer::registerTexture(TextureId texId) {
	TextureAtlas* atlas = m_resManager.getOrLoadTextureAtlas(texId.getResourceLocation());
	m_resManager.registerTexture(texId, atlas->getTexture(utils::Vector2u(0, 0)));
}

void ResourceRegisterer::registerAnimation(AnimationId animId, const std::vector<uint32_t>& animationLegths, float slideDuration) {
	TextureAtlas* atlas = m_resManager.getOrLoadTextureAtlas(animId.getResourceLocation());
	m_resManager.registerAnimation(animId, AnimationData(atlas, animationLegths, slideDuration));
}
