// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "AnimationData.h"

AnimationData::AnimationData(const TextureAtlas& atlas, const std::vector<uint32_t>& animationLengths, const float slideDuration)
	: m_slideDuration(slideDuration) {
	m_slides.resize(animationLengths.size());
	for (uint32_t id = 0; id < animationLengths.size(); id++) {
		m_slides[id].reserve(animationLengths[id]);

		for (uint32_t slide = 0; slide < animationLengths[id]; slide++) {
			m_slides[id].push_back(atlas.getTexture(math::Vector2u(slide, id)));
		}
	}
}

Texture& AnimationData::getTexture(const uint32_t animationId, const uint32_t slide) {
	return m_slides[animationId][slide];
}

float AnimationData::getSlideDuration() const {
	return m_slideDuration;
}

size_t AnimationData::getAnimationsCount() const {
	return m_slides.size();
}

size_t AnimationData::getAnimationSlideCount(const size_t id) const {
	return m_slides[id].size();
}
