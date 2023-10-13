// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Rect.h"

namespace math {
	// Allows to evaluate the possible movement according to the obstacles around
	class Collision final {
	private:
		Vector2f m_pos;
		Vector2f m_offset;
		SquareArray<bool, 3> m_obstacleMap;
		float m_hitbox;

	private:
		template<::utils::Callable<bool, int32_t, int32_t> ObstacleChecker>
		constexpr SquareArray<bool, 3> buildObstacleMap(ObstacleChecker isObstacle) const noexcept {
			SquareArray<bool, 3> result;

			for (int32_t x = -1; x <= 1; x++) {
				for (int32_t y = -1; y <= 1; y++) {
					result.at(x + 1ull, y + 1ull) = isObstacle(x, y);
				}
			}

			return result;
		}
 
	public:
		template<::utils::Callable<bool, int32_t, int32_t> ObstacleChecker>
		constexpr Collision(Vector2f pos, const float hitbox, Vector2f offset, ObstacleChecker isObstacle) noexcept
			: Collision(::std::move(pos), hitbox, ::std::move(offset), buildObstacleMap(isObstacle)) { }

		constexpr Collision(Vector2f pos, const float hitbox, Vector2f offset, SquareArray<bool, 3> obstacleMap) noexcept
			: m_pos(::std::move(pos)), m_hitbox(hitbox), m_offset(::std::move(offset)), m_obstacleMap(::std::move(obstacleMap)) { }

		constexpr Collision& calculatePossibleMove() noexcept {
			constexpr float EPSILON = float(2e-4); // Some small number

			// Handle the big offsets that can be generated after lags
			if (!m_offset.abs().isToUpLeftFrom({ 1, 1 })) {
				m_offset = m_offset.getMinByXY({ 1, 1 }).getMaxByXY({ -1, -1 });
			}

			Vector2f pos = m_pos - m_pos.roundFloor();
			Vector2f newPos = pos + Vector2f(m_offset.x(), 0.f);
			Vector2i currPos1 = (pos - m_hitbox).roundFloor().template to<int32_t>(); // top-left of the hitbox
			Vector2i currPos2 = (pos + m_hitbox).roundFloor().template to<int32_t>(); // down-right of the hitbox

			if (m_offset.x() < 0) {
				int32_t newX = static_cast<int32_t>(floor(newPos.x() - m_hitbox));
				if (m_obstacleMap.at(newX + 1ull, currPos1.y() + 1ull) || m_obstacleMap.at(newX + 1ull, currPos2.y() + 1ull)) {
					m_offset.x() = currPos1.x() - pos.x() + m_hitbox + EPSILON;
				}
			} else if (m_offset.x() > 0) {
				int32_t newX = static_cast<int32_t>(floor(newPos.x() + m_hitbox));
				if (m_obstacleMap.at(newX + 1ull, currPos1.y() + 1ull) || m_obstacleMap.at(newX + 1ull, currPos2.y() + 1ull)) {
					m_offset.x() = newX - pos.x() - m_hitbox - EPSILON;
				}
			}

			// Move according to the x offset
			pos.x() += m_offset.x();
			newPos = pos + Vector2f(0.f, m_offset.y());
			currPos1 = (pos - m_hitbox).roundFloor().template to<int32_t>(); // top-left of the hitbox
			currPos2 = (pos + m_hitbox).roundFloor().template to<int32_t>(); // down-right of the hitbox

			if (m_offset.y() < 0) {
				int32_t newY = int(floor(newPos.y() - m_hitbox));
				if (m_obstacleMap.at(currPos1.x() + 1, newY + 1) || m_obstacleMap.at(currPos2.x() + 1, newY + 1)) {
					m_offset.y() = currPos1.y() - pos.y() + m_hitbox + EPSILON;
				}
			} else if (m_offset.y() > 0) {
				int32_t newY = int(floor(newPos.y() + m_hitbox));
				if (m_obstacleMap.at(currPos1.x() + 1, newY + 1) || m_obstacleMap.at(currPos2.x() + 1, newY + 1)) {
					m_offset.y() = newY - pos.y() - m_hitbox - EPSILON;
				}
			}

			m_pos += m_offset;

			return *this;
		}

		constexpr Vector2f getOffset() const noexcept {
			return m_offset;
		}

		constexpr Vector2f getPos() const noexcept {
			return m_pos;
		}
	};
}