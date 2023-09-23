#pragma once
#include <vector>

#include "Utils/Vector.h"
#include "Graphics/Texture/Animation.h"
#include "Graphics/Camera.h"

class EntityRenderer final {
private:
	std::vector<Animation*> m_animations;
	std::vector<utils::Vector2f> m_positions;

public:
	void addAnimation(Animation* animation, const utils::Vector2f& position);

	void render(sf::RenderWindow& window, Camera& camera);
};