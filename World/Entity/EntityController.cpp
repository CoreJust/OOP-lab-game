// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityController.h"

#include "Math/Direction.h"
#include "Math/Rect.h"
#include "Math/Collision.h"
#include "Math/Cmath.h"
#include "World/World.h"
#include "IO/Logger.h"
#include "GlobalSettings.h"

EntityController::EntityController(std::unique_ptr<Entity> entity, World& pWorld)
	: m_entity(std::move(entity)), m_pWorld(pWorld) {

}

void EntityController::update(const float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	m_entity->getEffectPoolMut().update(deltaTime);

	if (m_isMoving) {
		m_animation->update(deltaTime);
		m_isMoving = false;
	} else {
		m_animation->reset();
	}

	for (const math::Vector2i& pos : math::Rectf(m_entity->getPos(), m_entity->getId().getEntityStats().hitbox)) {
		if (!m_pWorld.getMapper().contains(pos)) {
			continue;
		}

		for (uint8_t layer = 0; layer <= 1; layer++) {
			Tile& tile = m_pWorld.atMut(layer, pos);
			if (tile.isInteractive()) {
				tile.getTileData()->onStep(pos.to<float>(), m_pWorld, *m_entity);
			}
		}
	}
}

void EntityController::draw(RenderMaster& renderMaster) {
	renderMaster.drawEntity(*m_animation, m_entity->getPos() - 0.5f);
}

void EntityController::tryToMove(math::Vector2f offset) {
	// Updating animation
	math::Vector2f currentDirection;
	switch (m_animation->getAnimationId()) {
		case 0: currentDirection = math::Direction<float>::UP_VEC; break;
		case 1: currentDirection = math::Direction<float>::DOWN_VEC; break;
		case 2: currentDirection = math::Direction<float>::RIGHT_VEC; break;
		case 3: currentDirection = math::Direction<float>::LEFT_VEC; break;
	default: break;
	}

	float angle = offset.angleWith(currentDirection);
	if (abs(angle) > std::numbers::pi_v<float> / 4) {
		if (abs(offset.x()) >= abs(offset.y())) {
			if (offset.x() > 0) {
				m_animation->setAnimation(2); // right
			} else {
				m_animation->setAnimation(3); // left
			}
		} else {
			if (offset.y() > 0) {
				m_animation->setAnimation(1); // down
			} else {
				m_animation->setAnimation(0); // up
			}
		}
	}

	// Collision check

	if (!m_entity->isInSpiritualMode()) {
		offset = math::Collision(
			m_entity->getPos(),
			m_entity->getStats().hitbox,
			offset,
			[this, pos = m_entity->getPos().roundFloor().template to<int32_t>()](int32_t x, int32_t y) -> bool {
				return m_pWorld.isObstacleAt(pos + math::Vector2i(x, y));
			}
		).calculatePossibleMove().getOffset();
	}

	if (GlobalSettings::get().isToLogEntitiesPos()) {
		io::Logger::logInfo("Entity [" + m_entity->getId().toString() + "]: position: " + m_entity->getPos().toString()
						+ ", offset: " + offset.toString());
	}
	
	// Moving
	m_entity->move(offset);
	m_isMoving = true;
}

void EntityController::setAnimation(AnimationData& animationData) {
	m_animation = std::make_unique<Animation>(animationData);
}

float EntityController::calculateSpeed() const {
	float result = 0.f;
	math::Rectf entityRect = math::Rectf(m_entity->getPos(), m_entity->getStats().hitbox);
	math::SquareArray<float, 2> proportions = entityRect.getProportions<2>();

	math::Vector2i pos = entityRect.topLeft().roundFloor().to<int>();
	for (int32_t x = 0; x < 2; x++) {
		for (int32_t y = 0; y < 2; y++) {
			const Tile& tile = m_pWorld.at(0, pos + math::Vector2i { x, y });
			const Tile& tileFront = m_pWorld.at(1, pos + math::Vector2i { x, y });

			if (tile.isObstacle() || tileFront.isObstacle()) {
				result += proportions.at(x, y); // so that we don't get stuck in the wall in case something happened
			} else {
				float speedModifier = math::Cmath::min(tile.getId().getTileInfo().speedModifier, tileFront.getId().getTileInfo().speedModifier);
				result += proportions.at(x, y) * speedModifier;
			}
		}
	}

	return result * m_entity->getStats().speed;
}

Entity& EntityController::getEntity() {
	return *m_entity;
}
