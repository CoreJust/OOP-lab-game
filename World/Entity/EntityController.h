// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/NoNullptr.h"
#include "IO/Input/VirtualInput.h"
#include "Graphics/Render/RenderMaster.h"
#include "Entity.h"
#include "World/Effects/EffectPool.h"

/*
*	EntityController(.h/.cpp) contains a class that controls entities.
*
*	It acts as a mediator between an entity and the other parts of the game.
*	The class provides the behaviour of the entity (and there is a separate
*	*Controller for each Entity inheritor).
* 
*	This class is the base of all the other controllers.
* 
*	It handles the collisions, the effects put on the entity, the entities speed modifier,
*	it triggers the events that require stepping on some tile, and some other stuff.
*/

class World;

// Controls the behaviour of an entity, moves it around, checks for collisions
class EntityController {
protected:
	std::unique_ptr<Entity> m_entity;
	World& m_pWorld;

	std::unique_ptr<model::EntityModel> m_model;

public:
	EntityController(std::unique_ptr<Entity> entity, World& pWorld);

	virtual ~EntityController() = default;

	// Handles all the interactions with the world and other entities
	void update(const float deltaTime);
	virtual void draw(RenderMaster& renderMaster);

	// Tries to move in the direction
	// If a collision occured while moving, returns true
	bool tryToMove(math::Vector2f offset);

	float calculateSpeed() const; // Takes into account the basic speed and the speed mofifiers of tiles
	
	Entity& getEntity();
};