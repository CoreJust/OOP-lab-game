// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityRenderer.h"

void EntityRenderer::addAnimation(std::reference_wrapper<Animation> animation, const math::Vector2f& position) {
	m_animations.push_back(animation);
	m_positions.push_back(position);
}

void EntityRenderer::render(sf::RenderWindow& window, Camera& camera) {
	for (size_t i = 0; i < m_animations.size(); i++) {
		if (camera.isInView(m_positions[i])) {
			m_animations[i].get().render(window, camera.getPosInView(m_positions[i]), camera.getSingularObjectSize());
		}
	}

	m_animations.clear();
	m_positions.clear();
}
