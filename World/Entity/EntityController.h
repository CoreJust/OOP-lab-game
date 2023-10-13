// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/NoNullptr.h"
#include "IO/VirtualInput.h"
#include "Graphics/Render/RenderMaster.h"
#include "Graphics/Texture/Animation.h"
#include "Entity.h"
#include "World/Effects/EffectPool.h"

class World;

// Controls the behaviour of an entity, moves it around, checks for collisions
class EntityController {
protected:
	std::unique_ptr<Entity> m_entity;
	World& m_pWorld;

	std::unique_ptr<Animation> m_animation; // must be here to control animation states (e.g. the direction of moving)
	bool m_isMoving = false;

public:
	EntityController(std::unique_ptr<Entity> entity, World& pWorld);

	virtual ~EntityController() = default;

	// Handles all the interactions with the world and other entities
	virtual void update(const float deltaTime, utils::NoNullptr<io::VirtualInput> input);
	virtual void draw(RenderMaster& renderMaster);

	void tryToMove(math::Vector2f offset);
	void setAnimation(AnimationData& animationData);

	float calculateSpeed() const; // Takes into account the basic speed and the speed mofifiers of tiles
	
	Entity& getEntity();
};