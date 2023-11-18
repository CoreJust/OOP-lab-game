// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <random>

#include "Utils/Concepts.h"
#include "NoiseUtils.h"

/*
*	Based on PerlinNoise by Reputeless under MIT License: https://github.com/Reputeless/PerlinNoise/tree/master
* 
*	PerlinNoise.h contains a class that allows the generation of Perlin noise.
*
*	Perlin noise is a noise function that creates some kind of structure
*	suitable for generation of natural looking randomly shaped areas, e.g.
*	the fire texture of the islands map.
*/

namespace math {
	template<utils::FloatingPoint FloatTy>
	class PerlinNoise final {
	public:
		using NoiseUtils = NoiseUtils<FloatTy>;

		// Some kind-of-random values for noise with less than 3 dimensions
		// Somehow such non-zero values improve noise results
		constexpr inline static FloatTy DEFAULT_Y_VALUE = FloatTy(1.12358);
		constexpr inline static FloatTy DEFAULT_Z_VALUE = FloatTy(1.2624);

	private:
		uint8_t m_permutationTable[256]; // Internal state of noise

		FloatTy m_frequency; // the scale
		FloatTy m_persistance; // the raggedness - impact reduction of next octave
		FloatTy m_valueRange; // the noise output is normalized for [-valueRange; valueRange] or [0; valueRange]
		uint8_t m_octaveNumber; // number of noise octaves

	public:
		PerlinNoise(size_t seed, uint8_t octaveNumber, FloatTy frequency, FloatTy persistance, FloatTy valueRange)
			: m_frequency(frequency), m_persistance(persistance), m_valueRange(valueRange), m_octaveNumber(octaveNumber) {
			fillPermutationTable(seed);
		}

		// In range [0, m_valueRange]
		constexpr FloatTy rangedOctaveNoise(const FloatTy x) const noexcept {
			return MathUtils::remap0ToRange<FloatTy, FloatTy(1)>(octaveNoiseNormalized(x)) * m_valueRange;
		}

		// In range [0, m_valueRange]
		constexpr FloatTy rangedOctaveNoise(const FloatTy x, const FloatTy y) const noexcept {
			return MathUtils::remap0ToRange<FloatTy, FloatTy(1)>(octaveNoiseNormalized(x, y)) * m_valueRange;
		}

		// In range [0, m_valueRange]
		constexpr FloatTy rangedOctaveNoise(const FloatTy x, const FloatTy y, const FloatTy z) const noexcept {
			return MathUtils::remap0ToRange<FloatTy, FloatTy(1)>(octaveNoiseNormalized(x, y, z))* m_valueRange;
		}

		// In range [-1, 1]
		constexpr FloatTy octaveNoiseNormalized(const FloatTy x) const noexcept {
			return octaveNoise(x) / NoiseUtils::evalRangeOfOctaveNoise(m_persistance, m_octaveNumber);
		}

		// In range [-1, 1]
		constexpr FloatTy octaveNoiseNormalized(const FloatTy x, const FloatTy y) const noexcept {
			return octaveNoise(x, y) / NoiseUtils::evalRangeOfOctaveNoise(m_persistance, m_octaveNumber);
		}

		// In range [-1, 1]
		constexpr FloatTy octaveNoiseNormalized(const FloatTy x, const FloatTy y, const FloatTy z) const noexcept {
			return octaveNoise(x, y, z) / NoiseUtils::evalRangeOfOctaveNoise(m_persistance, m_octaveNumber);
		}

		constexpr FloatTy octaveNoise(FloatTy x) const noexcept {
			FloatTy result { 0 };
			FloatTy amplitude { 1 };

			x *= m_frequency;

			for (uint32_t i = 0; i < m_octaveNumber; i++) {
				result += noise(x) * amplitude;
				x *= 2;

				amplitude *= m_persistance;
			}

			return result;
		}

		constexpr FloatTy octaveNoise(FloatTy x, FloatTy y) const noexcept {
			FloatTy result { 0 };
			FloatTy amplitude { 1 };

			x *= m_frequency;
			y *= m_frequency;

			for (uint32_t i = 0; i < m_octaveNumber; i++) {
				result += noise(x, y) * amplitude;
				x *= 2;
				y *= 2;

				amplitude *= m_persistance;
			}

			return result;
		}

		constexpr FloatTy octaveNoise(FloatTy x, FloatTy y, FloatTy z) const noexcept {
			FloatTy result { 0 };
			FloatTy amplitude { 1 };

			x *= m_frequency;
			y *= m_frequency;
			z *= m_frequency;

			for (uint32_t i = 0; i < m_octaveNumber; i++) {
				result += noise(x, y, z) * amplitude;
				x *= 2;
				y *= 2;
				z *= 2;

				amplitude *= m_persistance;
			}

			return result;
		}

		constexpr FloatTy noise(const FloatTy x) const noexcept {
			return noise(x, DEFAULT_Y_VALUE, DEFAULT_Z_VALUE);
		}

		constexpr FloatTy noise(const FloatTy x, const FloatTy y) const noexcept {
			return noise(x, y, DEFAULT_Z_VALUE);
		}

		constexpr FloatTy noise(const FloatTy x, const FloatTy y, const FloatTy z) const noexcept {
			// Some math magic...
			// Actually, it is a more or less standard Perlin noise implementation

			const FloatTy _x = Cmath::floor(x);
			const FloatTy _y = Cmath::floor(y);
			const FloatTy _z = Cmath::floor(z);

			const int32_t ix = static_cast<int32_t>(_x) & 255;
			const int32_t iy = static_cast<int32_t>(_y) & 255;
			const int32_t iz = static_cast<int32_t>(_z) & 255;

			const FloatTy fx = (x - _x);
			const FloatTy fy = (y - _y);
			const FloatTy fz = (z - _z);

			const FloatTy u = NoiseUtils::quantic(fx);
			const FloatTy v = NoiseUtils::quantic(fy);
			const FloatTy w = NoiseUtils::quantic(fz);

			const uint8_t A = (m_permutationTable[ix & 255] + iy) & 255;
			const uint8_t B = (m_permutationTable[(ix + 1) & 255] + iy) & 255;

			const uint8_t AA = (m_permutationTable[A] + iz) & 255;
			const uint8_t AB = (m_permutationTable[(A + 1) & 255] + iz) & 255;

			const uint8_t BA = (m_permutationTable[B] + iz) & 255;
			const uint8_t BB = (m_permutationTable[(B + 1) & 255] + iz) & 255;

			const FloatTy p0 = NoiseUtils::grad(m_permutationTable[AA], fx, fy, fz);
			const FloatTy p1 = NoiseUtils::grad(m_permutationTable[BA], fx - 1, fy, fz);
			const FloatTy p2 = NoiseUtils::grad(m_permutationTable[AB], fx, fy - 1, fz);
			const FloatTy p3 = NoiseUtils::grad(m_permutationTable[BB], fx - 1, fy - 1, fz);
			const FloatTy p4 = NoiseUtils::grad(m_permutationTable[(AA + 1) & 255], fx, fy, fz - 1);
			const FloatTy p5 = NoiseUtils::grad(m_permutationTable[(BA + 1) & 255], fx - 1, fy, fz - 1);
			const FloatTy p6 = NoiseUtils::grad(m_permutationTable[(AB + 1) & 255], fx, fy - 1, fz - 1);
			const FloatTy p7 = NoiseUtils::grad(m_permutationTable[(BB + 1) & 255], fx - 1, fy - 1, fz - 1);

			const FloatTy q0 = NoiseUtils::lerp(p0, p1, u);
			const FloatTy q1 = NoiseUtils::lerp(p2, p3, u);
			const FloatTy q2 = NoiseUtils::lerp(p4, p5, u);
			const FloatTy q3 = NoiseUtils::lerp(p6, p7, u);

			const FloatTy r0 = NoiseUtils::lerp(q0, q1, v);
			const FloatTy r1 = NoiseUtils::lerp(q2, q3, v);

			return NoiseUtils::lerp(r0, r1, w);
		}

	private:
		void fillPermutationTable(size_t seed) {
			std::random_device rd;
			std::mt19937 gen(rd());
			gen.seed(seed);

			std::iota(m_permutationTable, m_permutationTable + 256, 0);
			std::shuffle(m_permutationTable, m_permutationTable + 256, gen);
		}
	};
}
