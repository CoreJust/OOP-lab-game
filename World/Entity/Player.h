// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Entity.h"

class World;

class Player final : public Entity {
public:
	Player(math::Vector2f pos, World& pWorld);

	math::Vector2f getViewPos() const;
};