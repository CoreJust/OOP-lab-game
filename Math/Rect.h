// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>

#include "Vector.h"
#include "SquareArray.h"

namespace math {
	// Literally a rectangle
	template<::utils::Arithmetic T>
	class Rect final {
	public:
		using VectorTy = Vector2<T>;
		using ValueTy = VectorTy::ValueTy;
		using FloatTy = VectorTy::FloatTy;

	private:
		VectorTy m_topLeft;
		VectorTy m_downRight;

	public:
		constexpr Rect() noexcept = default;
		constexpr Rect(const Rect&) noexcept = default;
		constexpr Rect(Rect&&) noexcept = default;

		constexpr Rect(VectorTy topLeft, VectorTy downRight) noexcept
			: m_topLeft(std::move(topLeft)), m_downRight(std::move(downRight)) {
			if (!m_topLeft.isToUpLeftFrom(m_downRight)) {
				m_downRight = m_topLeft; // collapsing the rect
			}
		}

		constexpr Rect(const VectorTy& center, T halfDiagonal) noexcept
			: m_topLeft(center - halfDiagonal), m_downRight(center + halfDiagonal) { }

		constexpr Rect& operator=(const Rect& other) noexcept {
			m_topLeft = other.topLeft();
			m_downRight = other.downRight();

			return *this;
		}

		constexpr Rect& operator=(Rect&& other) noexcept {
			m_topLeft = other.topLeft();
			m_downRight = other.downRight();

			return *this;
		}

		constexpr bool operator==(const Rect& other) const noexcept {
			return m_topLeft == other.topLeft() && m_downRight == other.downRight();
		}

		// Returns the percent of the rect's area for each of tiles (where tile [0, 0] is the tile of topLeft)
		template<uint32_t NumTiles>
		constexpr SquareArray<T, NumTiles> getProportions() const {
			SquareArray<T, NumTiles> result;
			T totalArea = getArea();
			VectorTy startPoint = m_topLeft.roundFloor();
			VectorTy topLeft = m_topLeft - startPoint;
			VectorTy downRight = m_downRight - startPoint;

			for (uint32_t x = 0; x < NumTiles; x++) {
				for (uint32_t y = 0; y < NumTiles; y++) {
					T localArea = Rect(topLeft.getMaxByXY({ x, y }), downRight.getMinByXY({ x + 1, y + 1 })).getArea();
					result.at(x, y) = (localArea / totalArea);
				}
			}

			return result;
		}

		constexpr bool contains(const VectorTy& point) const noexcept {
			return m_topLeft.isToUpLeftFrom(point) && m_downRight.isToDownRightFrom(point);
		}

		constexpr VectorTy& topLeft() noexcept {
			return m_topLeft;
		}

		constexpr const VectorTy& topLeft() const noexcept {
			return m_topLeft;
		}

		constexpr VectorTy& downRight() noexcept {
			return m_downRight;
		}

		constexpr const VectorTy& downRight() const noexcept {
			return m_downRight;
		}

		constexpr VectorTy getSize() const noexcept {
			return m_downRight - m_topLeft;
		}

		constexpr T getArea() const noexcept {
			return abs((m_downRight.x() - m_topLeft.x()) * (m_downRight.y() - m_topLeft.y()));
		}
	};

	using Rectf = Rect<Vector2f::ValueTy>;
	using Recti = Rect<Vector2i::ValueTy>;
	using Rectu = Rect<Vector2u::ValueTy>;
}