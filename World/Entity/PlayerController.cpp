// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PlayerController.h"

#include "Graphics/GameGUI/ProgressBar.h"
#include "Math/Direction.h"
#include "World/World.h"

PlayerContoller::PlayerContoller(std::unique_ptr<Player> player, World& pWorld)
	: EntityController(std::move(player), pWorld), m_healthBar(nullptr) {

}

void PlayerContoller::update(const float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	EntityController::update(deltaTime, input);

	math::Vector2f offset = math::Direction<float>::getDirectionVector(
		input->isKeyPressed(io::VirtualInput::KEY_UP),
		input->isKeyPressed(io::VirtualInput::KEY_DOWN),
		input->isKeyPressed(io::VirtualInput::KEY_RIGHT),
		input->isKeyPressed(io::VirtualInput::KEY_LEFT)
	);

	float shiftSpeedModifier = input->isKeyPressed(io::VirtualInput::KEY_ACCEL) ? 1.6f : 1;

	if (offset != math::Vector2f(0, 0)) {
		offset *= calculateSpeed() * shiftSpeedModifier * deltaTime;

		tryToMove(offset);
	}
}

void PlayerContoller::draw(RenderMaster& renderMaster) {
	EntityController::draw(renderMaster);

	// Drawing GUI
	m_healthBar->setValue(m_entity->getHealth() / m_entity->getStats().maxHealth);
}

void PlayerContoller::initGUI(RenderMaster& renderMaster, Camera& camera) {
	math::Vector2f topLeftOfHealth { -1.f + 0.05f };
	constexpr math::Vector2f healthBarSize { 0.8f, 0.08f };

	if (m_healthBar) { // In case of repetitive invocations
		renderMaster.getGameGuiRenderer().eraseGameGUI(m_healthBar);
	}

	m_healthBar = renderMaster.getGameGuiRenderer().registerGameGUI<gamegui::ProgressBar>(
		/*Name =*/			"Health", 
		/*Pos =*/			math::Rectf(topLeftOfHealth, topLeftOfHealth + healthBarSize),
		/*Bar color =*/		sf::Color::Red,
		/*Outline color =*/ sf::Color::White
	);
}

Player& PlayerContoller::getPlayer() {
	return *(Player*)m_entity.get();
}
