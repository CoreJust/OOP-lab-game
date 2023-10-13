// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Vector.h"

// Anything that can be located in the world
class WorldObject {
protected:
	math::Vector2f m_pos;

public:
	WorldObject(math::Vector2f pos);

	const math::Vector2f& getPos() const;
	float getX() const;
	float getY() const;
};