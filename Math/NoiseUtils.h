// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cmath>
#include "Utils/Concepts.h"
#include "MathUtils.h"

/*
*	NoiseUtils.h contains a class with a set of static auxiliary math functions.
*
*	These functions are generally used for the noise generation, thus the name.
*/

namespace math {
	template<utils::FloatingPoint FloatTy>
	class NoiseUtils final {
	public:
		constexpr static FloatTy quantic(const FloatTy t) {
			return t * t * t * (t * (t * 6 - 15) + 10);
		}

		// Linear interpolation of t for t = [0, 1] into [a, b] (as far as I am concerned)
		constexpr static FloatTy lerp(const FloatTy a, const FloatTy b, const FloatTy t) {
			return a + (b - a) * t;
		}

		constexpr static FloatTy grad(const uint8_t hash, const FloatTy x, const FloatTy y, const FloatTy z) {
			const uint8_t h = hash & 15;
			const FloatTy u = h < 8 ? x : y;
			const FloatTy v = (h < 4) ? y : (h == 12 || h == 14) ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

		constexpr static FloatTy evalRangeOfOctaveNoise(const FloatTy persistance, const int32_t octaves) {
			return MathUtils::geometricProgression(1.f, persistance, octaves);
		}
	};
}