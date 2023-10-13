// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <memory>
#include "Math/Vector.h"

class World;
class Player;

// An interface that handles all the interactions with a tile, its unique qualities, etc
// Cannot be used as is, must be inherited
class TileData {
protected:
	TileData() = default;

public:
	virtual ~TileData() noexcept = default;

	virtual void update(math::Vector2f pos, World& world, Player& player) = 0;

	// Expected to be used with smart pointers
	virtual std::unique_ptr<TileData> copy() = 0;
};