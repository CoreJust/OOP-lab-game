// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GameGUIRenderer.h"
#include <cassert>

void GameGUIRenderer::eraseGameGUI(gamegui::GameGUI* gui) {
	for (auto it = m_guis.begin(); it != m_guis.end(); it++) {
		if (it->get() == gui) {
			m_guis.erase(it);
			return;
		}
	}

	assert(false && "GUI not found");
}

void GameGUIRenderer::render(sf::RenderWindow& window, Camera& camera) {
	sf::Transform transform;
	transform.scale(camera.getGuiTransform().toSfml());

	for (auto& gui : m_guis) {
		gui->render(window, transform);
	}
}
