// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "EnemyBehaviour.h"
#include "Math/Rasterizer/LineRasterizer.h"
#include "Math/Cmath.h"
#include "Utils/Random.h"
#include "World/World.h"

bool EnemyBehaviour::isPlayerInAttackRange(const math::Vector2f& pos, const math::Vector2f& playerPos) const {
    return pos.distance(playerPos) <= m_attackRange;
}

math::Vector2f EnemyBehaviour::getAttractionPoint(
    const World& world,
    const math::Vector2f& pos,
    const math::Vector2f& playerPos,
    const math::Vector2f& currentAttractionPoint
) {
    if (currentAttractionPoint.distance(playerPos) < 0.5f) {
        return currentAttractionPoint; // for optimization purposes
    }

    if (currentAttractionPoint.distance(pos) > 0.5f) {
        if (isPlayerInSight(world, pos, playerPos)) {
            m_isPursuing = true;
            m_lastPlayerPosInSight = playerPos;
            return getAttackAttractionPoint(world, pos, playerPos);
        } else {
            return currentAttractionPoint;
        }
    }

    if (pos.distance(playerPos) > m_pursuitRange) {
        m_isPursuing = false;
        return getMoveAttractionPoint(world, pos, playerPos);
    }

    if (isPlayerInSight(world, pos, playerPos)) {
        m_isPursuing = true;
        m_lastPlayerPosInSight = playerPos;
        return getAttackAttractionPoint(world, pos, playerPos);
    } else {
        if (m_attackPolicy != EnemyAttackPolicy::PROACTIVE_PURSUIT) {
            m_isPursuing = false;
        }

        if (m_isPursuing) {
            const math::Vector2f AAP = getAttackAttractionPoint(world, pos, playerPos);
            if (pos.distance(AAP) < 0.15f) {
                return getMoveAttractionPoint(world, pos, playerPos);
            } else {
                return AAP;
            }
        } else {
            return getMoveAttractionPoint(world, pos, playerPos);
        }
    }
}

bool EnemyBehaviour::isPlayerInSight(const World& world, const math::Vector2f& pos, const math::Vector2f& playerPos) const {
    if (pos.distance(playerPos) > m_sightRange) {
        return false;
    }

    math::LineRasterizer rast(pos, playerPos);
    while (rast.hasMore()) {
        int32_t y = rast.getY();
        for (int32_t x = rast.leftX(); x <= rast.rightX(); x++) {
            if (world.at(false, { x, y }).getCategory() == TileCategory::WALL) {
                return false;
            }
        }

        rast.nextRow();
    }

    return true;
}

math::Vector2f EnemyBehaviour::getAttackAttractionPoint(
    const World& world, 
    const math::Vector2f& pos, 
    const math::Vector2f& playerPos
) const {
    switch (m_attackPolicy) {
        case EnemyAttackPolicy::IGNORE: return getMoveAttractionPoint(world, pos, playerPos);
        case EnemyAttackPolicy::PASSIVE_PURSUIT: return playerPos;
        case EnemyAttackPolicy::INERTIAL_PURSUIT: return m_lastPlayerPosInSight;
        case EnemyAttackPolicy::PROACTIVE_PURSUIT: return getAttractionOnPathToPlayer(world, pos, playerPos);
    default: return pos;
    }
}

math::Vector2f EnemyBehaviour::getMoveAttractionPoint(
    const World& world,
    const math::Vector2f& pos, 
    const math::Vector2f& playerPos
) const {
    if (m_movePolicy == EnemyMovePolicy::STRAIGHT_ROAMING) {
        const float moveLength = utils::Random<>::rand(100, 1000) / 100.f;
        switch (utils::Random<>::rand(0, 3)) {
            case 0: return pos + math::Vector2f(moveLength, 0.f);
            case 1: return pos + math::Vector2f(-moveLength, 0.f);
            case 2: return pos + math::Vector2f(0.f, moveLength);
            case 3: return pos + math::Vector2f(0.f, -moveLength);
        default: return pos + math::Vector2f(0.f, 0.f);
        }
    }

    const uint32_t signs = utils::Random<>::rand<uint32_t>(0, 3);
    const float _cos = ((signs & 1) ? 1.f : -1.f) * utils::Random<>::rand(0, 128) / 128.f;
    const float _sin = ((signs & 2) ? 1.f : -1.f) * math::Cmath::sqrt(1.f - _cos * _cos);
    assert(_cos <= 1.f && _cos >= -1.f);
    assert(_sin <= 1.f && _sin >= -1.f);

    const float moveLength = utils::Random<>::rand(100, 1000) / 100.f;
    math::Vector2f attractionPoint = math::Vector2f(_cos, _sin) * moveLength;

    switch (m_movePolicy) {
        case EnemyMovePolicy::NO_MOVING: attractionPoint = 0; break;
        case EnemyMovePolicy::RANDOM_ROAMING: break;
        case EnemyMovePolicy::CLOSING_ON_PLAYER: {
            const float angleToPlayer = (pos - attractionPoint).angleWith(pos - playerPos);
            attractionPoint = attractionPoint.rotate(angleToPlayer * 0.1f);
        } break;
    default: attractionPoint = 0; break;
    }

    // Checking for the movement's possibility
    /*
    const math::Recti recti((pos - 0.5f).roundFloor().to<int32_t>(), (pos + 0.5f).roundFloor().to<int32_t>());
    const math::Vector2i posi = pos.roundFloor().to<int32_t>();
    bool isNoUp = world.isObstacleAt({ posi.x(), recti.top() });
    bool isNoDown = world.isObstacleAt({ posi.x(), recti.down() });
    bool isNoRight = world.isObstacleAt({ recti.right(), posi.y() });
    bool isNoLeft = world.isObstacleAt({ recti.left(), posi.y() });
    if (isNoDown && isNoUp) {
        attractionPoint.y() = 0;
    } else if ((isNoUp && attractionPoint.y() < 0) || (isNoDown && attractionPoint.y() > 0)) {
        attractionPoint.y() = -attractionPoint.y();
    }

    if (isNoRight && isNoLeft) {
        attractionPoint.x() = 0;
    } else if ((isNoLeft && attractionPoint.x() < 0) || (isNoRight && attractionPoint.x() > 0)) {
        attractionPoint.x() = -attractionPoint.x();
    }
    */

    // Checking for world's bounds
    attractionPoint += pos;
    attractionPoint.x() = math::MathUtils::clamp<float>(attractionPoint.x(), -world.getSize().x(), world.getSize().x() + 1);
    attractionPoint.y() = math::MathUtils::clamp<float>(attractionPoint.y(), -world.getSize().y(), world.getSize().y() + 1);

    return attractionPoint;
}

math::Vector2f EnemyBehaviour::getAttractionOnPathToPlayer(
    const World& world, 
    const math::Vector2f& pos, 
    const math::Vector2f& playerPos
) const {
    // Temporary solution
    // TODO: review
    return m_lastPlayerPosInSight;
}
