// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GameState.h"
#include "IO/Logger.h"

constexpr math::Vector2u WORLD_SIZE = { 40, 40 };

GameState::GameState()
	: m_world(WORLD_SIZE),
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
}

void GameState::render(sf::RenderWindow& window) {
	if (sf::Vector2u size = window.getSize(); m_camera.updateViewSize(math::Vector2f(size.x, size.y))) {
		// m_playerController.initGUI(m_renderMaster, m_camera); // deprecated
	}

	m_world.draw(m_renderMaster, m_camera);
	m_playerController.draw(m_renderMaster);

	m_renderMaster.render(window, m_camera);
}
