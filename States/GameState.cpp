#include "GameState.h"

GameState::GameState()
	: State(),
	m_playerController(std::make_unique<Player>(utils::Vector2f(0.5, 0.5)), &m_world),
	m_world({ 6, 6 })
{
	m_playerController.setAnimation(m_renderMaster.getResources().getAnimationData(AnimationId::PLAYER));
}

void GameState::update(float deltaTime) {
	m_playerController.update(deltaTime);
	m_camera.setPos(m_playerController.getPlayer().getPos());

	m_world.update(m_playerController.getPlayer(), deltaTime);
}

void GameState::render(sf::RenderWindow& window) {
	sf::View view = window.getView();
	m_camera.updateViewSize(utils::Vector2f(view.getSize().x, view.getSize().y));

	m_world.draw(m_renderMaster, m_camera);
	m_playerController.draw(m_renderMaster);

	m_renderMaster.render(window, m_camera);
}
