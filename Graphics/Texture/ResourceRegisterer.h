// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "ResourceManager.h"

class ResourceRegisterer final {
private:
	ResourceManager& m_resManager;

public:
	ResourceRegisterer(ResourceManager& resManager);

	void registerAll();

private:
	void registerTexture(const TextureId texId);
	void registerAnimation(
		const AnimationId animId,
		const std::vector<uint32_t>& animationLegths, 
		const float slideDuration = 0.3
	);
};