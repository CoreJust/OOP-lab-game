// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <vector>
#include "Utils/Random.h"

/*
*	ChanceDistribution.h contains a class that allows to distribute the probability.
*
*	The general idea is that we have a set of mutually exclusive outcomes with some chances.
*	Than we can feed them and their probabilities to the class and for each random value 
*	get the outcome according to their probabilities.
* 
*	Usage:
*		utils::Random<...> random;
*		math::ChanceDistribution<decltype(random)::RG, -outcome type-> chanceDist(random, -default outcome-);
*		chanceDist.push(-chance-, -outcome-);
*		chanceDist.push(-chance-, -outcome-);
*		size_t someChanceIndex = chanceDist.push(-chance-, -outcome-); // allows to modify the chance
*
*		...
* 
*		-type- outcome = chanceDist.pick(); // Picking a random outcome according to the probabilities
*		if (...) {
*			chanceDist.setChance(someChanceIndex, -new chance-);
*		}
*/

namespace math {
	// Allows to have to choose a random value according to chances
	template<class T, class Value, bool IgnoreChanceOverflow = false>
	class ChanceDistribution final {
	private:
		utils::Random<T>& m_random;
		std::vector<float> m_chances;
		std::vector<Value> m_values;
		Value m_defaultValue;

	public:
		ChanceDistribution(utils::Random<T>& random, Value defaultValue) noexcept
			: m_random(random), m_defaultValue(std::move(defaultValue)) { }

		// Returns the index of chance allowing to modify it
		size_t push(float chance, Value value) {
			float lastChance = m_chances.size() ? m_chances.back() : 0.f;

			if constexpr (!IgnoreChanceOverflow) {
				assert(lastChance + chance <= 1.f);
			}

			m_chances.push_back(lastChance + chance);
			m_values.emplace_back(std::move(value));

			return m_chances.size() - 1;
		}

		const Value& pick() {
			float randValue = m_random.random(0, 100'000) / 100'000.f;

			if (m_chances.size() == 0 || randValue > m_chances.back()) {
				return m_defaultValue;
			}

			for (size_t i = 0; i < m_chances.size(); i++) {
				if (randValue <= m_chances[i]) {
					return m_values[i];
				}
			}

			assert(false && "unreachable");
		}

		void setChance(size_t i, float chance) {
			assert(i < m_chances.size());

			float currChance = getChance(i);
			if (currChance != chance) {
				float diff = chance - currChance;

				if constexpr (!IgnoreChanceOverflow) {
					assert(m_chances.back() + diff <= 1.f);
				}

				for (size_t j = i; j < m_chances.size(); j++) {
					m_chances[j] += diff;
				}
			}
		}

		float getChance(size_t i) const {
			assert(i < m_chances.size());

			if (i == 0) {
				return m_chances[i];
			}

			return m_chances[i] - m_chances[i - 1];
		}

		const Value& getValue(size_t i) const {
			assert(i < m_chances.size());

			return m_values[i];
		}

		size_t size() const noexcept {
			return m_chances.size();
		}
	};
}