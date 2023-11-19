// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Game.h"
#include "IO/Logger.h"
#include "Graphics/GameGUI/MessageDialog.h"

Game::Game()
	: m_display(800, 600, "OOP lab5 game"), m_stateManager(m_display.getMouseWheelDeltaRef()) {
	gamegui::MessageDialog::initGUI(m_display.getWindow());
	io::Logger::logInfo("Initialized GameGUI module");
}

void Game::run() {
	while (m_display.isOpen()) {
		m_display.update();

		m_stateManager.update(m_display.getWindow(), m_timer.calculateDeltaTime());

		if (m_stateManager.isToBeClosed()) {
			break;
		}

		m_display.display();
	}

	m_display.close();
}
