#include "EntityController.h"

#include "Utils/Direction.h"
#include "World/World.h"

EntityController::EntityController(std::unique_ptr<Entity> entity, World* pWorld)
	: m_entity(std::move(entity)), m_pWorld(pWorld) {

}

void EntityController::update(float deltaTime) {
	if (m_isMoving) {
		m_animation->update(deltaTime);
		m_isMoving = false;
	} else {
		m_animation->reset();
	}
}

void EntityController::draw(RenderMaster& renderMaster) {
	renderMaster.drawEntity(m_animation.get(), m_entity->getPos() - 0.5);
}

void EntityController::tryToMove(utils::Vector2f offset) {
	// Updating animation
	utils::Vector2f currentDirection;
	switch (m_animation->getAnimationId()) {
		case 0: currentDirection = utils::Direction<float>::UP_VEC; break;
		case 1: currentDirection = utils::Direction<float>::DOWN_VEC; break;
		case 2: currentDirection = utils::Direction<float>::RIGHT_VEC; break;
		case 3: currentDirection = utils::Direction<float>::LEFT_VEC; break;
	default: break;
	}

	float angle = offset.angleWith(currentDirection);
	if (abs(angle) > utils::PI / 4) {
		if (abs(offset.x()) >= abs(offset.y())) {
			if (offset.x() > 0) {
				m_animation->setAnimation(2); // right
			} else {
				m_animation->setAnimation(3); // left
			}
		} else {
			if (offset.y() > 0) {
				m_animation->setAnimation(0); // up
			} else {
				m_animation->setAnimation(1); // down
			}
		}
	}

	// Collision check

	float hitbox = m_entity->getStats().hitbox;
	const utils::Vector2f& entityPos = m_entity->getPos();

	// Current position in the world
	utils::Vector2i currPos1 = (entityPos - hitbox).roundFloor();
	utils::Vector2i currPos2 = (entityPos + hitbox).roundFloor();

	// newPos1 and newPos2 is a hitbox of the entity
	utils::Vector2i newPos1 = (entityPos + offset - hitbox).roundFloor();
	utils::Vector2i newPos2 = (entityPos + offset + hitbox).roundFloor();

	if (newPos1.x() < currPos1.x()) {
		if (m_pWorld->isObstacleAt({ newPos1.x(), currPos1.y() })) {
			offset.x() = currPos1.x() - entityPos.x() + hitbox;
		}
	} else if (newPos2.x() > currPos2.x()) {
		if (m_pWorld->isObstacleAt({ newPos2.x(), currPos2.y() })) {
			offset.x() = newPos2.x() - entityPos.x() - hitbox - 2e-5f;
		}
	}

	if (newPos1.y() < currPos1.y()) {
		if (m_pWorld->isObstacleAt({ currPos1.x(), newPos1.y() })) {
			offset.y() = currPos1.y() - entityPos.y() + hitbox;
		}
	} else if (newPos2.y() > currPos2.y()) {
		if (m_pWorld->isObstacleAt({ currPos2.x(), newPos2.y() })) {
			offset.y() = newPos2.y() - entityPos.y() - hitbox - 2e-5f;
		}
	}
	
	// Moving
	m_entity->move(offset);
	m_isMoving = true;
}

void EntityController::setAnimation(AnimationData* animationData) {
	m_animation = std::make_unique<Animation>(animationData);
}

Entity& EntityController::getEntity() {
	return *m_entity;
}
