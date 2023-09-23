#include "AnimationData.h"

AnimationData::AnimationData(TextureAtlas* atlas, const std::vector<uint32_t>& animationLengths, float slideDuration)
	: m_slideDuration(slideDuration) {
	m_slides.resize(animationLengths.size());
	for (uint32_t id = 0; id < animationLengths.size(); id++) {
		m_slides[id].reserve(animationLengths[id]);

		for (uint32_t slide = 0; slide < animationLengths[id]; slide++) {
			m_slides[id].push_back(atlas->getTexture(utils::Vector2u(slide, id)));
		}
	}
}

Texture& AnimationData::getTexture(uint32_t animationId, uint32_t slide) {
	return m_slides[animationId][slide];
}

float AnimationData::getSlideDuration() const {
	return m_slideDuration;
}

size_t AnimationData::getAnimationsCount() const {
	return m_slides.size();
}

size_t AnimationData::getAnimationSlideCount(size_t id) const {
	return m_slides[id].size();
}
