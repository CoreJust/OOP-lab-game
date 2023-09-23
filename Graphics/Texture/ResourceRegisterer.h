#pragma once
#include "ResourceManager.h"

class ResourceRegisterer final {
private:
	ResourceManager& m_resManager;

public:
	ResourceRegisterer(ResourceManager& resManager);

	void registerAll();

private:
	void registerTexture(TextureId texId);
	void registerAnimation(
		AnimationId animId,
		const std::vector<uint32_t>& animationLegths, 
		float slideDuration = 0.3
	);
};