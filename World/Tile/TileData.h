#pragma once
#include "Utils/Vector.h"

class World;
class Player;

// An interface that handles all the interactions with a tile, its unique qualities, etc
// Cannot be used as is, must be inherited
class TileData {
protected:
	TileData() = default;

public:
	virtual void update(utils::Vector2f pos, World* world, Player* player) = 0;
};