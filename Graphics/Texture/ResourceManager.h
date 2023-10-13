// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <map>
#include <memory>

#include "AnimationId.h"
#include "TextureId.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "AnimationData.h"

// Manages images/animations/...
class ResourceManager final {
protected:
	std::map<std::string, std::unique_ptr<TextureAtlas>> m_atlases;
	std::vector<Texture> m_textures;
	std::vector<AnimationData> m_animations;

public:
	ResourceManager();

	TextureAtlas& getOrLoadTextureAtlas(const std::string& name);

	void registerTexture(const TextureId texId, Texture texture);
	void registerAnimation(const AnimationId animId, AnimationData animation);

	Texture& getTexture(const TextureId texId);
	AnimationData& getAnimationData(const AnimationId animId);
};