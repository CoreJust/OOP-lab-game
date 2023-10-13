// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>

#include "Math/Vector.h"
#include "Graphics/Texture/Animation.h"
#include "Graphics/Camera.h"

class EntityRenderer final {
private:
	std::vector<std::reference_wrapper<Animation>> m_animations;
	std::vector<math::Vector2f> m_positions;

public:
	void addAnimation(std::reference_wrapper<Animation> animation, const math::Vector2f& position);

	void render(sf::RenderWindow& window, Camera& camera);
};