// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cmath>
#include <cassert>

#include "Utils/Concepts.h"
#include "Cmath.h"

/*
*	MathUtils.h contains a class with a set of static auxiliary math functions.
*/

namespace math {
	class MathUtils final {
	public:
		// Remaps the value from [-Range, Range] to [0, Range]
		template<utils::Arithmetic T, T Range>
		constexpr static T remap0ToRange(const T x) {
			const T halfRange = Range / 2;
			return halfRange + halfRange * x;
		}

		// Puts the number in range [From; To)
		// Examples: encycle<int, 0, 4>(6) == 2 or encycle<int, -1, 1>(1) == -1
		template<utils::Arithmetic T, T From, T To>
		constexpr static T encycle(const T x) {
			static_assert(From < To);

			constexpr T rangeLength = To - From;
			if constexpr (From != 0) {
				return encycle<T, T(0), rangeLength>(x - From) + From;
			}

			// From == 0 here, so [0; To)
			if (x < 0) {
				const float mult = math::Cmath::ceil(x / -To);
				return x + To * mult;
			} else if (x >= To) {
				const float mult = math::Cmath::floor(x / To);
				return x - To * mult;
			}

			return x;
		}
		
		// Puts the number in range [-Range; Range)
		template<utils::Arithmetic T, T Range>
		constexpr static T encycleInRange(const T x) {
			static_assert(Range > 0);

			return encycle<T, -Range, Range>(x);
		}

		template<utils::Arithmetic T>
		constexpr static T clamp(const T x, const T from, const T to) {
			assert(from < to);

			return x < from
				? from
				: x > to
				? to
				: x;
		}

		// Clamps the value in bounds of [From, To]
		template<utils::Arithmetic T, T From, T To>
		constexpr static T clamp(const T x) {
			static_assert(From < To);

			return x < From
				? From
				: x > To
					? To
					: x;
		}

		// Clamps the value in bounds of [-Range, Range]
		template<utils::Arithmetic T, T Range>
		constexpr static T clampInRange(const T x) {
			static_assert(Range > 0);

			return clamp<T, -Range, Range>(x);
		}

		// Combination of remap and clampInRange functions
		template<utils::Arithmetic T, T Range>
		constexpr static T remapAndClamp(const T x) {
			static_assert(Range > 0);

			if (x <= -Range) {
				return T(0);
			} else if (x >= Range) {
				return Range;
			}

			return remap0ToRange<T, Range>(x);
		}

		// Sums up the first n elements of progression first + first * q + ... + first * q**n
		template<utils::Arithmetic T>
		constexpr static T geometricProgression(const T first, const T q, const int32_t n) {
			assert(n > 0);

			return (first * (Cmath::pow(q, n) - 1)) / (q - 1);
		}

		// Sums up the first n elements of a custom progression
		template<utils::Arithmetic T, utils::Callable<T, T> NextElement>
		constexpr static T customProgression(T first, int32_t n, NextElement next) {
			T result = static_cast<T>(0);

			while (n-- > 0) {
				result += first;
				first = next(first);
			}
		}
	};
}