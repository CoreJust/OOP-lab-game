// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GameState.h"
#include "IO/Logger/Logger.h"
#include "IO/Message/PlayerLostMessage.h"
#include "World/LevelLoader.h"
#include "Graphics/GameGUI/MessageDialog.h"
#include "Graphics/GameGUI/PlayTime.h"
#include "StateManager.h"

GameState::GameState(StateManager& pManager)
	: RenderableState(pManager),
	m_world(),
	m_playerController(std::make_unique<Player>(m_world), m_world)
{
	LevelLoader(m_world, m_playerController.getPlayer(), true).loadLevel(WorldLevelId::BASIC_LEVEL);

	m_camera.addRotationCallback(m_playerController.createOnRotation());
	m_camera.setFOV(50.f);

	m_playerController.initGUI(m_renderMaster, m_camera);
	m_renderMaster.getPlayTime()->reset();

	io::Logger::trace("GameState: initialized");
}

void GameState::freeze() {
	// Nothing in here
}

void GameState::revive() {
	m_renderMaster.getPlayTime()->reset();
}

void GameState::update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	m_playerController.update(deltaTime, input);
	m_camera.update(input);
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

	m_renderMaster.setPlayerData(m_playerController.getPlayer());
	m_world.draw(m_renderMaster, m_camera);
	m_playerController.draw(m_renderMaster);

	m_renderMaster.render(window, m_camera);
}

void GameState::processPlayerDeath() {
	io::Logger::info("GameState: player died");
	io::Logger::message(io::PlayerLostMessage(m_playerController.getPlayer().getPos()));

	gamegui::MessageDialog dialog("Game message", "You died! One more try?", "I have some confidence", "Accept defeat");
	if (dialog.open() == 2) { // Accepted defeat
		io::Logger::info("GameState: player accepted defeat");

		m_pManager.popState();
		return;
	}

	io::Logger::info("GameState: restarting the game");
	LevelLoader(m_world, m_playerController.getPlayer(), true).loadLevel(WorldLevelId::BASIC_LEVEL);
	m_renderMaster.getPlayTime()->reset();
	io::Logger::debug("GameState: game restarted successfully");
}
