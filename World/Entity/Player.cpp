// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Player.h"

Player::Player(const math::Vector2f& pos, const float rot, World& pWorld) 
	: Entity(pos, rot, EntityId::PLAYER, pWorld) { }

Player::Player(World& pWorld)
	: Player({ 0.5f, 0.5f }, 0.f, pWorld) { }

math::Vector2f Player::getViewPos() const {
	return getPos();
}
