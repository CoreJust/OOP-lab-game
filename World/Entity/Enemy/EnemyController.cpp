// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EnemyController.h"
#include "Math/Cmath.h"
#include "World/Entity/Player.h"

EnemyController::EnemyController(std::unique_ptr<EnemyBase> enemy, World& pWorld) 
	: EntityController(std::move(enemy), pWorld), m_attractionPoint(m_entity->getPos()) {

}

void EnemyController::update(const float deltaTime, Player& player) {
	auto& behaviour = getBehaviour();
	if (behaviour.isPlayerInAttackRange(m_entity->getPos(), player.getPos())) {
		attackPlayer(deltaTime, player);
	} else {
		m_attractionPoint = behaviour.getAttractionPoint(m_pWorld, m_entity->getPos(), player.getPos(), m_attractionPoint);
		math::Vector2f currentMove = m_attractionPoint - m_entity->getPos();
		if (currentMove.length() < 0.1f) {
			return;
		}

		m_entity->setRotation(currentMove.rotation());

		currentMove = currentMove * (calculateSpeed() * deltaTime / currentMove.length());
		if (EntityController::tryToMove(currentMove)) {
			m_attractionPoint = m_entity->getPos(); // Stop moving there
		}
	}

	EntityController::update(deltaTime);
}

void EnemyController::draw(RenderMaster& renderMaster) {
	EntityController::draw(renderMaster);
}

EnemyBase& EnemyController::getEnemy() {
	return *(EnemyBase*)m_entity.get();
}

EnemyBehaviour& EnemyController::getBehaviour() {
	return getEnemy().getBehaviour();
}

void EnemyController::attackPlayer(const float deltaTime, Player& player) {
	m_attackCooldown = math::Cmath::max(0.f, m_attackCooldown - deltaTime);
	if (m_attackCooldown <= 0.001f) { // Close to zero
		getEnemy().onAttack(m_pWorld, player);
		m_attackCooldown = 5.f / m_entity->getStats().agility;
	}
}
