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
	AnimationData(TextureAtlas* atlas, const std::vector<uint32_t>& animationLengths, float slideDuration = 0.3f);

	Texture& getTexture(uint32_t animationId, uint32_t slide);

	float getSlideDuration() const;
	size_t getAnimationsCount() const;
	size_t getAnimationSlideCount(size_t id) const;
};