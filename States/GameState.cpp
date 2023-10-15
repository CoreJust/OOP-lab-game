// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GameState.h"
#include "IO/Logger.h"
#include "Graphics/GameGUI/MessageDialog.h"

GameState::GameState()
	: m_world(WorldLevelId::BASIC_LEVEL),
	m_playerController(std::make_unique<Player>(math::Vector2f(0.5, 0.5), m_world), m_world)
{
	m_playerController.setAnimation(m_renderMaster.getResources().getAnimationData(AnimationId::PLAYER));
	m_playerController.initGUI(m_renderMaster, m_camera);

	io::Logger::logInfo("Initialized GameState");
}

void GameState::update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	m_playerController.update(deltaTime, input);
	m_camera.setPos(m_playerController.getPlayer().getViewPos());

	m_world.update(m_playerController.getPlayer(), deltaTime);

	if (!m_playerController.getPlayer().isAlive()) {
		processPlayerDeath();
	}
}

void GameState::render(sf::RenderWindow& window) {
	if (sf::Vector2u size = window.getSize(); m_camera.updateViewSize(math::Vector2f(size.x, size.y))) {
		// m_playerController.initGUI(m_renderMaster, m_camera); // deprecated
	}

	m_world.draw(m_renderMaster, m_camera);
	m_playerController.draw(m_renderMaster);

	m_renderMaster.render(window, m_camera);
}

void GameState::processPlayerDeath() {
	io::Logger::logInfo("Player died. Restarting game...");

	gamegui::MessageDialog dialog("Game message", "You died! Restarting the game");
	dialog.open();

	m_world = World(WorldLevelId::BASIC_LEVEL);
	m_playerController.getPlayer() = Player(math::Vector2f(0.5, 0.5), m_world);

	io::Logger::logInfo("Game restarted successfully");
}
