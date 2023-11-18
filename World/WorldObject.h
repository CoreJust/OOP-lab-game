// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Math/Vector.h"

/*
*	WorldObject(.h/.cpp) contains a base class for all the objects that are represented
*	in the world and can move around (mostly and currently the only inheritor of the class
*	is the Entity).
*/

// Anything that can be located in the world
class WorldObject {
protected:
	math::Vector2f m_pos;
	float m_rot;

public:
	constexpr WorldObject(const math::Vector2f& pos, float rot) noexcept : m_pos(pos), m_rot(rot) { }

	constexpr float getRot() const noexcept {
		return m_rot;
	}

	constexpr const math::Vector2f& getPos() const noexcept {
		return m_pos;
	}

	constexpr float getX() const noexcept {
		return m_pos.x();
	}

	constexpr float getY() const noexcept {
		return m_pos.y();
	}
};