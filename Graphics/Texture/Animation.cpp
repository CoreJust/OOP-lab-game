// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Animation.h"

#include <cassert>

Animation::Animation(AnimationData& animation, const uint32_t animationId, const uint32_t animationSlide)
	: m_animation(animation), m_animationId(animationId), m_animationSlide(animationSlide) {

}

void Animation::setAnimation(const uint32_t id) {
	assert(id < m_animation.getAnimationsCount());

	m_animationId = id;
	m_animationSlide = 0;
	m_slideTimer = 0;
}

void Animation::update(const float deltaTime) {
	if (m_animation.getAnimationSlideCount(m_animationId) <= 1) {
		return;
	}

	m_slideTimer += deltaTime;

	if (m_slideTimer >= m_animation.getSlideDuration()) {
		int32_t numberSlidesToSkip = int32_t(m_slideTimer / m_animation.getSlideDuration());
		m_slideTimer -= numberSlidesToSkip * m_animation.getSlideDuration();

		m_animationSlide = (m_animationSlide + numberSlidesToSkip) % m_animation.getAnimationSlideCount(m_animationId);
	}
}

void Animation::render(sf::RenderWindow& window, const math::Vector2f& pos, const math::Vector2f& scale) {
	m_animation.getTexture(m_animationId, m_animationSlide).render(window, pos, scale);
}

void Animation::reset() {
	m_animationSlide = 0;
	m_slideTimer = 0;
}

uint32_t Animation::getAnimationId() const {
	return m_animationId;
}

uint32_t Animation::getAnimationSlide() const {
	return m_animationSlide;
}