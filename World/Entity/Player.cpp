// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Player.h"

Player::Player(const math::Vector2f& pos, const float rot, World& pWorld) 
	: Entity(pos, rot, EntityId::PLAYER, pWorld) { }

Player::Player(World& pWorld)
	: Player({ 0.5f, 0.5f }, 0.f, pWorld) { }

void Player::dealDamageToPlayer(const float damage, const EntityId attacker) {
	Entity::dealDamage(damage);

	io::Logger::debug(std::format("Player: damage dealt to player by entity {0} : {1}, pure damage: {2:.1f}",
								  attacker.toString(), int(damage), Entity::calcDamage(damage)));
	
	if (!isAlive()) {
		io::Logger::info(std::format("Player: killed by an entity {0}, damage {1}, pure damage {2:.1f}",
									 attacker.toString(), int(damage), Entity::calcDamage(damage)));
	}
}

void Player::dealDamageToPlayer(const float damage, const EffectId attacker) {
	Entity::dealDamage(damage);

	io::Logger::debug(std::format("Player: damage dealt to player by effect {0} : {1}, pure damage: {2:.1f}",
								  attacker.toString(), int(damage), Entity::calcDamage(damage)));

	if (!isAlive()) {
		io::Logger::info(std::format("Player: killed by an effect {0}, damage {1}, pure damage {2:.1f}",
									 attacker.toString(), int(damage), Entity::calcDamage(damage)));
	}
}

math::Vector2f Player::getViewPos() const {
	return getPos();
}
