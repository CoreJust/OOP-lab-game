// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GameGUI.h"

void gamegui::GameGUI::render(sf::RenderWindow& window, const sf::Transform& transform) {
	for (auto& d : m_drawables) {
		window.draw(*d, transform);
	}
}

void gamegui::GameGUI::move(const math::Vector2f& pos) {
	for (auto& d : m_drawables) {
		sf::Transformable& t = *(sf::Transformable*)d.get();
		t.move(pos.toSfml());
	}
}

void gamegui::GameGUI::clear() {
	m_drawables.clear();
}
