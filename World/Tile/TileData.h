// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <memory>
#include "Math/Vector.h"

/*
*	TileData.h contains a base class for a family of TileDatas.
*
*	TileDatas represent all the additional qualities attached to a tile
*	apart from those dictated by its ID and declared in the corresponding TileInfo.
* 
*	The additional qualities are: any additional data (for example some stored item)
*	as well as the events caused by an entity stepping onto the tile. Also, the TileData
*	manages the updates of the tile.
* 
*	Unlike basic characteristics that are bound to an ID, the TileData is generally assigned
*	based on the ID, but can then be changed (internally or externally) or reassigned/initially
*	assigned in a different way rather than the expected. Thus objects like a stone with teleportation
*	or any other abilities can be created.
*/

class World;
class Player;
class Entity;

// An interface that handles all the interactions with a tile, its unique qualities, etc
// Cannot be used as is, must be inherited
class TileData {
protected:
	TileData() = default;

public:
	virtual ~TileData() noexcept = default;

	virtual void update(math::Vector2f pos, World& world, Player& player, const float deltaTime) = 0;
	virtual void onStep(math::Vector2f pos, World& world, Entity& entity) = 0; // On entity stepping on the tile

	// Expected to be used with smart pointers
	virtual std::unique_ptr<TileData> copy() = 0;
};