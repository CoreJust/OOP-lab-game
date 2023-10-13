// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>

#include "Texture.h"
#include "TextureAtlas.h"

// Contains an animation, but does not play it
class AnimationData final {
protected:
	std::vector<std::vector<Texture>> m_slides;
	float m_slideDuration = 0;

public:
	AnimationData() = default;
	AnimationData(const TextureAtlas& atlas, const std::vector<uint32_t>& animationLengths, const float slideDuration = 0.3f);

	Texture& getTexture(const uint32_t animationId, const uint32_t slide);

	float getSlideDuration() const;
	size_t getAnimationsCount() const;
	size_t getAnimationSlideCount(const size_t id) const;
};