#pragma once
#include "Graphics/Render/RenderMaster.h"
#include "Entity.h"

class World;

// Controls the behaviour of an entity, moves it around, checks for collisions
class EntityController {
protected:
	std::unique_ptr<Entity> m_entity;
	World* m_pWorld;

	std::unique_ptr<Animation> m_animation; // must be here to control animation states (e.g. the direction of moving)
	bool m_isMoving = false;

public:
	EntityController(std::unique_ptr<Entity> entity, World* pWorld);

	// Handles all the interactions with the world and other entities
	virtual void update(float deltaTime);
	virtual void draw(RenderMaster& renderMaster);

	void tryToMove(utils::Vector2f offset);
	void setAnimation(AnimationData* animationData);
	
	Entity& getEntity();
};