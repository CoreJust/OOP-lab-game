#include "PlayerController.h"

#include <SFML/Window/Keyboard.hpp>

#include "Utils/Direction.h"
#include "World/World.h"

PlayerContoller::PlayerContoller(std::unique_ptr<Player> player, World* pWorld)
	: EntityController(std::move(player), pWorld) {

}

void PlayerContoller::update(float deltaTime) {
	EntityController::update(deltaTime);

	utils::Vector2f offset = utils::Direction<float>::getDirectionVector(
		sf::Keyboard::isKeyPressed(sf::Keyboard::W),
		sf::Keyboard::isKeyPressed(sf::Keyboard::S),
		sf::Keyboard::isKeyPressed(sf::Keyboard::D),
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)
	);

	float shiftSpeedModifier = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 1.6f : 1;

	if (offset != utils::Vector2f(0, 0)) {
		offset *= getPlayer().getStats().speed * shiftSpeedModifier * deltaTime;

		tryToMove(offset);
	}
}

Player& PlayerContoller::getPlayer() {
	return *(Player*)m_entity.get();
}
