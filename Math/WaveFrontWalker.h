// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <set>
#include "Utils/Concepts.h"
#include "Vector.h"

/*
*	WaveFrontWalker.h contains a class that allows to walk through some cavities
*	using the wave front.
* 
*	The general underlying principle is that we have a map and some point on it.
*	For some purpose, we need to walk through all the points on the map that are
*	connected with the point (that is, they are located in the same cavity/area).
*	To do so, we use a "wave" that is being triggered in the point and then goes
*	in all the directions.
* 
*	This scheme allows to access all the points within the cavity once:
* 
*	Some sketches (step by step) to understand the class's work:
*		(W - the wall, . - the cavity, @ - the wave front, x - the old wave front)
* 
*		Step 1:
*		W W W W W W W W
*		W W W W . W W W
*		W . . . . . . W
*		W W W . @ . W W
*		. . W . . . W W
*		. . W W W W W W
* 
*		Step 2:
*		W W W W W W W W
*		W W W W . W W W
*		W . . . @ . . W
*		W W W @ x @ W W
*		. . W . @ . W W
*		. . W W W W W W
* 
*		Step 3:
*		W W W W W W W W
*		W W W W @ W W W
*		W . . @ x @ . W
*		W W W x . x W W
*		. . W @ x @ W W
*		. . W W W W W W
* 
*		Step 4:
*		W W W W W W W W
*		W W W W x W W W
*		W . @ x . x @ W
*		W W W . . . W W
*		. . W x . x W W
*		. . W W W W W W
* 
*		Step 5:
*		W W W W W W W W
*		W W W W . W W W
*		W @ x . . . x W
*		W W W . . . W W
*		. . W . . . W W
*		. . W W W W W W
* 
*	Usage:
*		math::WaveFrontWalker<-condition type-, false/true> walker(-point-, -condition-);
*		math::Vector2i walkerPos;
*
*		while (walker.next(walkerPos)) {
*			... here we have a point of another positions
*			This code would be executed for each point within the cavity.
*		}
*/

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