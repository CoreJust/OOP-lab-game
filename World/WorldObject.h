#pragma once
#include "Utils/Vector.h"

// Anything that can be located in the world
class WorldObject {
protected:
	utils::Vector2f m_pos;

public:
	WorldObject(utils::Vector2f pos);

	const utils::Vector2f& getPos() const;
	float getX() const;
	float getY() const;
};