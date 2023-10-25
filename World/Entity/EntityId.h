// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"
#include "EntityStats.h"

/*
*	EntityId(.h/.cpp) contains a class that represents the entity Id - the type of entity.
*
*	The entities differ based on their Ids and the classes.
*	The basic entity class represent a basic entity - with no behaviour of its own.
*	So the class of the entity represents its behaviour.
* 
*	Unlike entity class, its Id represents the characteristics of the entity - those that
*	are common for all the entities - EntityStats and entity's visual part - its texture (and animation).
* 
*	It is similar to how we have TileId and different TileDatas. Thus EntityId is the static part
*	of a certain entities definition.
* 
*	As of now, there is only one entity presented - the player (this is going to change soon though).
*/

class EntityId : public BasicId {
public:
	enum Value : id_t {
		PLAYER = 0,

		NUMBER_ENTITY_IDS
	};

public:
	constexpr EntityId() = delete;
	constexpr EntityId(Value value) noexcept : BasicId(value) {
		assert(value < NUMBER_ENTITY_IDS);
	}

	constexpr EntityId& operator=(EntityId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	const EntityStats& getEntityStats() const;

	std::string toString() const override;
};