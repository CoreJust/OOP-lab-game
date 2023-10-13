// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <chrono>
#include <random>

#include "Concepts.h"

namespace utils {
	// Class for convenient random usage
	template<RandomGeneratorConcept RandomGenerator = std::mt19937>
	class Random final {
	private:
		RandomGenerator m_rand;

	public:
		inline void setSeed(size_t seed) {
			m_rand.seed(seed);
		}

		template<class T, DistributionConcept<T> Distribution = std::uniform_int_distribution<T>>
			requires std::is_arithmetic_v<T>
		inline T random(T from, T to) {
			Distribution dist(from, to);

			return dist(m_rand);
		}

		template<class T, DistributionConcept<T> Distribution = std::uniform_int_distribution<T>>
			requires std::is_arithmetic_v<T>
		inline static T rand(T from, T to) {
			static Random<RandomGenerator> s_random;

			return s_random.random<T, Distribution>(from, to);
		}
	};
}