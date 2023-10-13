// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Vector.h"

namespace math {
	enum DirectionFlag : uint8_t {
		NONE = 0,
		UP = 1,
		DOWN = 2,
		RIGHT = 4,
		LEFT = 8
	};

	template<utils::Arithmetic T>
		requires std::is_signed_v<T>
	struct Direction {
		// The distance of length 1 diagonally, for floating points it is 1/sqrt(2)
		// For integers it is 1, since it is the nearest whole to 1/sqrt(2)
		constexpr static T DIAGONAL_VALUE = std::is_integral_v<T> ? 1 : (T(1) / std::numbers::sqrt2_v<T>);

		constexpr static Vector2<T> UP_VEC = Vector2<T>(0, -1);
		constexpr static Vector2<T> DOWN_VEC = Vector2<T>(0, 1);
		constexpr static Vector2<T> RIGHT_VEC = Vector2<T>(1, 0);
		constexpr static Vector2<T> LEFT_VEC = Vector2<T>(-1, 0);

		constexpr static Vector2<T> UP_RIGHT_VEC = Vector2<T>(DIAGONAL_VALUE, -DIAGONAL_VALUE);
		constexpr static Vector2<T> DOWN_RIGHT_VEC = Vector2<T>(DIAGONAL_VALUE, DIAGONAL_VALUE);
		constexpr static Vector2<T> UP_LEFT_VEC = Vector2<T>(-DIAGONAL_VALUE, -DIAGONAL_VALUE);
		constexpr static Vector2<T> DOWN_LEFT_VEC = Vector2<T>(-DIAGONAL_VALUE, DIAGONAL_VALUE);

		// Converts a set of direction flags into a Vector2
		constexpr static Vector2<T> getDirectionVector(uint8_t directionBits) {
			if (directionBits & UP && directionBits & DOWN) directionBits ^= UP | DOWN;
			if (directionBits & RIGHT && directionBits & LEFT) directionBits ^= RIGHT | LEFT;

			switch (directionBits) {
				case UP: return UP_VEC;
				case DOWN: return DOWN_VEC;
				case RIGHT: return RIGHT_VEC;
				case LEFT: return LEFT_VEC;
				case UP | RIGHT: return UP_RIGHT_VEC;
				case DOWN | RIGHT: return DOWN_RIGHT_VEC;
				case UP | LEFT: return UP_LEFT_VEC;
				case DOWN | LEFT: return DOWN_LEFT_VEC;
			default: return Vector2<T>(0, 0);
			}
		}


		constexpr static Vector2<T> getDirectionVector(const bool up, const bool down, const bool right, const bool left) {
			return getDirectionVector(
				(up ? UP : NONE)
				| (down ? DOWN : NONE)
				| (right ? RIGHT : NONE)
				| (left ? LEFT : NONE)
			);
		}
	};
}