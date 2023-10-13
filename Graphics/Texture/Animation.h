// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "AnimationData.h"

// Allows to play an animation
// Animation is a sequence of pictures with some switch time in between
class Animation final {
private:
	AnimationData& m_animation;

	uint32_t m_animationId = 0;
	uint32_t m_animationSlide = 0;
	float m_slideTimer = 0;

public:
	Animation(AnimationData& animation, const uint32_t animationId = 0, const uint32_t animationSlide = 0);

	void setAnimation(const uint32_t id);

	void update(const float deltaTime);
	void render(sf::RenderWindow& window, const math::Vector2f& pos, const math::Vector2f& scale = { 1, 1 });

	void reset();

	uint32_t getAnimationId() const;
	uint32_t getAnimationSlide() const;
};