#include "WorldObject.h"

WorldObject::WorldObject(utils::Vector2f pos)
    : m_pos(std::move(pos)) {

}

const utils::Vector2f& WorldObject::getPos() const {
    return m_pos;
}

float WorldObject::getX() const {
    return m_pos.x();
}

float WorldObject::getY() const {
    return m_pos.y();
}
