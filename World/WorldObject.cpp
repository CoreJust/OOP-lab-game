// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "WorldObject.h"

WorldObject::WorldObject(math::Vector2f pos)
    : m_pos(std::move(pos)) {

}

const math::Vector2f& WorldObject::getPos() const {
    return m_pos;
}

float WorldObject::getX() const {
    return m_pos.x();
}

float WorldObject::getY() const {
    return m_pos.y();
}
