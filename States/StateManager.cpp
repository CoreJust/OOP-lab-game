#include "StateManager.h"

#include "GameState.h"

StateManager::StateManager() {
	m_menus.push_back(std::make_unique<GameState>());
}

void StateManager::update(sf::RenderWindow& window, float deltaTime) {
	getCurrentMenu()->update(deltaTime);
	getCurrentMenu()->render(window);

	if (m_popMenu) {
		m_popMenu = false;
		m_menus.pop_back();

		m_isToExit = m_menus.size() == 0;
	}
}

void StateManager::addMenu(std::unique_ptr<State> menu) {
	m_menus.push_back(std::move(menu));
}

void StateManager::popMenu() {
	m_popMenu = true;
}

State* StateManager::getCurrentMenu() const {
	return m_menus.back().get();
}

bool StateManager::isToBeClosed() const {
	return m_isToExit;
}
