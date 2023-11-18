// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PlayerController.h"

#include "Graphics/GameGUI/ProgressBar.h"
#include "Graphics/GameGUI/Text.h"
#include "Math/Direction.h"
#include "World/World.h"

PlayerContoller::PlayerContoller(std::unique_ptr<Player> player, World& pWorld)
	: EntityController(std::move(player), pWorld), m_healthBar(nullptr), m_infoText(nullptr) {

}

void PlayerContoller::update(const float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	EntityController::update(deltaTime, input);

	math::Vector2f offset = math::Direction<float>::getDirectionVector(
		input->isKeyPressed(io::KEY_UP),
		input->isKeyPressed(io::KEY_DOWN),
		input->isKeyPressed(io::KEY_RIGHT),
		input->isKeyPressed(io::KEY_LEFT)
	);

	float shiftSpeedModifier = input->isKeyPressed(io::KEY_ACCEL) ? 1.6f : 1;

	if (offset != math::Vector2f(0, 0)) {
		offset *= calculateSpeed() * shiftSpeedModifier * deltaTime;

		tryToMove(offset);
	}
}

void PlayerContoller::draw(RenderMaster& renderMaster) {
	EntityController::draw(renderMaster);

	// Drawing GUI
	m_healthBar->setValue(m_entity->getHealth() / m_entity->getStats().maxHealth);
	m_infoText->setText("Player: " + m_entity->getPos().toString());
}

void PlayerContoller::initGUI(RenderMaster& renderMaster, Camera& camera) {
	math::Vector2f topLeftOfHealth { -1.f + 0.05f };
	constexpr math::Vector2f healthBarSize { 0.8f, 0.08f };

	math::Vector2f topLeftOfInfotext = topLeftOfHealth + math::Vector2f(0.f, healthBarSize.y() * 1.2f);
	constexpr math::Vector2f infotextSize { 0.5f, 0.07f };

	if (m_healthBar) { // In case of repetitive invocations
		renderMaster.getGameGuiRenderer().eraseGameGUI(m_healthBar);
	}

	if (m_infoText) {
		renderMaster.getGameGuiRenderer().eraseGameGUI(m_infoText);
	}

	m_healthBar = renderMaster.getGameGuiRenderer().registerGameGUI<gamegui::ProgressBar>(
		/*Name =*/			"Health", 
		/*Pos =*/			math::Rectf(topLeftOfHealth, topLeftOfHealth + healthBarSize),
		/*Bar color =*/		sf::Color::Red,
		/*Outline color =*/ sf::Color::White
	);

	m_infoText = renderMaster.getGameGuiRenderer().registerGameGUI<gamegui::Text>(
		"Player: ", math::Rectf(topLeftOfInfotext, topLeftOfInfotext + infotextSize), 20
	);
}

Camera::RotationCallback PlayerContoller::createOnRotation() {
	return [this](const math::Vector2f& rot) { 
		getPlayer().setRotation(-rot.x()); // 'cause the camera's rotation is the opposite of the entities rotation
	};
}

Player& PlayerContoller::getPlayer() {
	return *(Player*)m_entity.get();
}
