#pragma once
#include "AnimationData.h"

// Allows to play an animation
class Animation final {
private:
	AnimationData* m_animation;

	uint32_t m_animationId = 0;
	uint32_t m_animationSlide = 0;
	float m_slideTimer = 0;

public:
	Animation(AnimationData* animation, uint32_t animationId = 0, uint32_t animationSlide = 0);

	void setAnimation(uint32_t id);

	void update(float deltaTime);
	void render(sf::RenderWindow& window, const utils::Vector2f& pos);

	void reset();

	uint32_t getAnimationId() const;
	uint32_t getAnimationSlide() const;
};