#include "EntityRenderer.h"

void EntityRenderer::addAnimation(Animation* animation, const utils::Vector2f& position) {
	m_animations.push_back(animation);
	m_positions.push_back(position);
}

void EntityRenderer::render(sf::RenderWindow& window, Camera& camera) {
	for (size_t i = 0; i < m_animations.size(); i++) {
		if (camera.isInView(m_positions[i])) {
			m_animations[i]->render(window, camera.getPosInView(m_positions[i]));
		}
	}

	m_animations.clear();
	m_positions.clear();
}
