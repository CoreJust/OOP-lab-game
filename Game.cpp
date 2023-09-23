#include "Game.h"

Game::Game()
	: m_display(800, 600, "OOP lab1 game") {

}

void Game::run() {
	while (m_display.isOpen()) {
		m_display.pollEvents();

		m_stateManager.update(m_display.getWindow(), m_timer.calculateDeltaTime());

		if (m_stateManager.isToBeClosed()) {
			break;
		}

		m_display.display();
	}
}
