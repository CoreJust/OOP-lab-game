// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <set>
#include "Utils/Concepts.h"
#include "Vector.h"

namespace math {
	// Allows to once walk through all the cells in some area that meets some requirement
	// Uses wave front algorithm
	// If condition somehow takes into account the already walked through values, the AccountAlreadeWalked might be set to false
	template<utils::Callable<bool, Vector2i> Condition, bool AccountAlreadyWalked = true>
	class WaveFrontWalker final {
	private:
		using HashedOldFrontTy = std::conditional_t<AccountAlreadyWalked, std::set<uint64_t>, bool>;

	private:
		Condition m_condition; // Must return true if position belongs to the cluster

		HashedOldFrontTy m_hashedOldFront;
		std::set<uint64_t> m_hashedCurrFront;
		std::vector<math::Vector2i> m_waveFront;
		size_t m_index;

	private:
		uint64_t hash(const Vector2i& pos) const noexcept {
			return uint64_t(pos.y() | (uint64_t(pos.x()) << 32));
		}

		// Returns true if new front is not empty and false otherwises
		bool buildNewFront() {
			constexpr static Vector2i s_VonNeumannNeighbourhood[4] {
				Vector2i(1, 0),
				Vector2i(0, 1),
				Vector2i(-1, 0),
				Vector2i(0, -1)
			};

			std::vector<Vector2i> newFront;
			std::set<uint64_t> newHashedFront;

			m_index = 0;
			if constexpr (AccountAlreadyWalked) {
				for (const Vector2i& pos : m_waveFront) {
					for (const Vector2i& offset : s_VonNeumannNeighbourhood) {
						Vector2i newPos = pos + offset;
						uint64_t newPosHash = hash(newPos);
						if (m_condition(newPos) && !m_hashedOldFront.contains(newPosHash) && !m_hashedCurrFront.contains(newPosHash) && !newHashedFront.contains(newPosHash)) {
							newFront.push_back(newPos);
							newHashedFront.insert(newPosHash);
						}
					}
				}

				m_waveFront = std::move(newFront);
				m_hashedOldFront = std::move(m_hashedCurrFront);
				m_hashedCurrFront = std::move(newHashedFront);
			} else {
				for (const Vector2i& pos : m_waveFront) {
					for (const Vector2i& offset : s_VonNeumannNeighbourhood) {
						Vector2i newPos = pos + offset;
						uint64_t newPosHash = hash(newPos);
						if (m_condition(newPos) && !m_hashedCurrFront.contains(newPosHash) && !newHashedFront.contains(newPosHash)) {
							newFront.push_back(newPos);
							newHashedFront.insert(newPosHash);
						}
					}
				}

				m_waveFront = std::move(newFront);
				m_hashedCurrFront = std::move(newHashedFront);
			}

			return m_waveFront.size() != 0;
		}

	public:
		WaveFrontWalker(const Vector2i& initialPos, Condition condition) noexcept
			: m_condition(std::move(condition)), m_waveFront({ initialPos }), m_hashedCurrFront({ hash(initialPos) }), m_index(0) { }

		// Returns true if there is the next cell and false otherwise
		bool next(Vector2i& result) {
			if (m_index >= m_waveFront.size()) {
				if (!buildNewFront()) {
					return false;
				}
			}

			result = m_waveFront[m_index++];
			return true;
		}
	};
}