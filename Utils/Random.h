// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <chrono>
#include <random>

#include "Concepts.h"

/*
*	Random.h contains a class that implements access to Random numbers.
* 
*	The class allows 2 schemes of usage:
*	1) Local:
*		utils::Random<...> rd;
* 
*		rd.setSeed(...);
*		int value = rd.random(-range from-, -range to-);
* 
*	2) Static:
*		...
*		utils::Random<...>::initRandom();
*		utils::Random<...>::setStaticSeed(...);
*		...
* 
*		int value = utils::Random<...>::rand(-range from-, -range to-);
* 
*		...
*		utils::Random<...>::destroyRandom();
*		...
*/

namespace utils {
	// Class for convenient random usage
	template<RandomGeneratorConcept RandomGenerator = std::mt19937>
	class Random final {
	public:
		using RG = RandomGenerator;

	private:
		RandomGenerator m_rand;

	private:
		inline static Random* s_random = nullptr;

	public:
		inline void setSeed(size_t seed) {
			m_rand.seed(seed);
		}

		template<class T, DistributionConcept<T> Distribution = std::uniform_int_distribution<
				std::conditional_t<std::is_signed_v<T>, int64_t, uint64_t>>
			>
			requires std::is_arithmetic_v<T>
		T random(T from, T to) {
			Distribution dist(from, to);

			return T(dist(m_rand));
		}

		constexpr const RandomGenerator& getRG() const noexcept {
			return m_rand;
		}

	public:
		inline static void initRandom() {
			assert(!s_random);

			s_random = new Random();
		}

		inline static void setStaticSeed(size_t seed) {
			assert(s_random);

			s_random->setSeed(seed);
		}

		inline static void destroyRandom() {
			assert(s_random);

			delete s_random;
		}

		template<class T, DistributionConcept<T> Distribution = std::uniform_int_distribution<T>>
			requires std::is_arithmetic_v<T>
		static T rand(T from, T to) {
			assert(s_random);

			return s_random->random<T, Distribution>(from, to);
		}
	};
}