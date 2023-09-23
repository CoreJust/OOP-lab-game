#include "Player.h"

Player::Player(utils::Vector2f pos)
	: Entity(std::move(pos), EntityId::PLAYER) {

}
