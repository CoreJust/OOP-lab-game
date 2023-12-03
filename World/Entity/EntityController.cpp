// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EntityController.h"

#include "Math/Direction.h"
#include "Math/Rect.h"
#include "Math/Collision.h"
#include "Math/Cmath.h"
#include "World/World.h"
#include "IO/Logger/Logger.h"
#include "GlobalSettings.h"

EntityController::EntityController(std::unique_ptr<Entity> entity, World& pWorld)
	: m_entity(std::move(entity)), 
	m_pWorld(pWorld),
	m_model(std::make_unique<model::EntityModel>(m_entity->getId())) {

}

void EntityController::update(const float deltaTime) {
	m_entity->getEffectPoolMut().update(deltaTime);

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
	m_model->sceneObject().pos.x = m_entity->getX();
	m_model->sceneObject().pos.z = m_entity->getY();

	renderMaster.drawEntity(m_entity->getId(), *m_model);
}

bool EntityController::tryToMove(math::Vector2f offset) {
	// Collision check

	const math::Vector2f originalOffset = offset;
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
		io::Logger::info("EntityController: Entity [" + std::string(m_entity->getId().toString()) + "]: position: "
						 + m_entity->getPos().toString() + ", offset: " + offset.toString());
	}
	
	// Moving
	m_entity->move(offset);

	if (offset.x() || offset.y()) {
		m_model->sceneObject().rot.y = -offset.rotationNegOY();
	}

	return originalOffset != offset;
}

float EntityController::calculateSpeed() const {
	float result = 0.f;
	math::Rectf entityRect = math::Rectf(m_entity->getPos(), m_entity->getStats().hitbox);
	math::SquareArray<float, 2> proportions = entityRect.getProportions<2>();

	math::Vector2i pos = entityRect.topLeft().roundFloor().to<int>();
	for (int32_t x = 0; x < 2; x++) {
		for (int32_t y = 0; y < 2; y++) {
			const math::Vector2i tilePos = pos + math::Vector2i(x, y);
			if (m_pWorld.isObstacleAt(tilePos)) {
				result += proportions.at(x, y); // so that we don't get stuck in the wall in case something happened
			} else {
				const Tile& tile = m_pWorld.at(0, tilePos);
				const Tile& tileFront = m_pWorld.at(1, tilePos);
				const float speedModifier = math::Cmath::min(tile.getId().getTileInfo().speedModifier, tileFront.getId().getTileInfo().speedModifier);
				result += proportions.at(x, y) * speedModifier;
			}
		}
	}

	return result * m_entity->getStats().speed;
}

Entity& EntityController::getEntity() {
	return *m_entity;
}
