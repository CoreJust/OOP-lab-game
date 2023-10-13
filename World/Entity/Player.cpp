// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Player.h"

Player::Player(math::Vector2f pos, World& pWorld)
	: Entity(std::move(pos), EntityId::PLAYER, pWorld) {

}

math::Vector2f Player::getViewPos() const {
	return getPos() - math::Vector2f(0, 1);
}
