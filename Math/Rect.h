// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>

#include "Vector.h"
#include "SquareArray.h"
#include "RectIterator.h"

/*
*	Rect.h contains a class that implements a rectangle.
*
*	Rect<T> consists of 2 vectors. It allows a number of operations
*	over some rectangular area.
*/

namespace math {
	// Literally a rectangle
	template<::utils::Arithmetic T>
	class Rect final {
	public:
		using VectorTy = Vector2<T>;
		using ValueTy = VectorTy::ValueTy;
		using FloatTy = VectorTy::FloatTy;
		using IntegralTy = VectorTy::IntegralTy;

		using Iterator = RectIterator<IntegralTy>;

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

		constexpr Rect(ValueTy left, ValueTy top, ValueTy right, ValueTy down) noexcept
			: Rect(VectorTy(left, top), VectorTy(right, down)) { }

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

		constexpr Rect operator-() const noexcept {
			return Rect(-m_topLeft, -m_downRight);
		}

		constexpr Rect operator+(const ValueTy val) const noexcept {
			return Rect(m_topLeft + val, m_downRight + val);
		}

		constexpr Rect operator-(const ValueTy val) const noexcept {
			return Rect(m_topLeft - val, m_downRight - val);
		}

		constexpr Rect operator*(const ValueTy val) const noexcept {
			return Rect(m_topLeft * val, m_downRight * val);
		}

		constexpr Rect operator/(const ValueTy val) const noexcept {
			return Rect(m_topLeft / val, m_downRight / val);
		}

		constexpr Rect& operator+=(const ValueTy val) noexcept {
			m_topLeft += val;
			m_downRight += val;
			return *this;
		}

		constexpr Rect& operator-=(const ValueTy val) noexcept {
			m_topLeft -= val;
			m_downRight -= val;
			return *this;
		}

		constexpr Rect& operator*=(const ValueTy val) noexcept {
			m_topLeft *= val;
			m_downRight *= val;
			return *this;
		}

		constexpr Rect& operator/=(const ValueTy val) noexcept {
			m_topLeft /= val;
			m_downRight /= val;
			return *this;
		}

		template<utils::Arithmetic U>
		constexpr Rect<U> to() const noexcept {
			return Rect<U>(m_topLeft.to<U>(), m_downRight.to<U>());
		}

		constexpr Rect clip(const VectorTy& fromTopLeft, const VectorTy& fromDownRight) const noexcept {
			return Rect(m_topLeft + fromTopLeft, m_downRight - fromDownRight);
		}

		constexpr Rect clip(T n) const noexcept {
			return Rect(m_topLeft + n, m_downRight - n);
		}

		constexpr Rect multByCoords(const VectorTy& vec) const noexcept {
			return Rect(m_topLeft.x() * vec.x(), m_topLeft.y() * vec.y(), m_downRight.x() * vec.x(), m_downRight.y() * vec.y());
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

		constexpr VectorTy getCenter() const noexcept {
			return m_topLeft + (m_downRight - m_topLeft) / 2;
		}

		constexpr bool contains(const VectorTy& point) const noexcept {
			return m_topLeft.isToUpLeftFrom(point) && m_downRight.isToDownRightFrom(point);
		}

		constexpr const Iterator begin() const noexcept {
			return Iterator(
				m_topLeft.roundFloor().to<IntegralTy>(),
				static_cast<IntegralTy>(Cmath::floor(m_topLeft.x())),
				static_cast<IntegralTy>(Cmath::floor(m_downRight.x())) + 1
			);
		}

		constexpr const Iterator end() const noexcept {
			return Iterator(
				math::Vector2<IntegralTy>(
					static_cast<IntegralTy>(Cmath::floor(m_topLeft.x())), 
					static_cast<IntegralTy>(Cmath::floor(m_downRight.y())) + 1
				),
				static_cast<IntegralTy>(Cmath::floor(m_topLeft.x())),
				static_cast<IntegralTy>(Cmath::floor(m_downRight.x())) + 1
			);
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

		constexpr ValueTy top() const noexcept {
			return m_topLeft.y();
		}

		constexpr ValueTy down() const noexcept {
			return m_downRight.y();
		}

		constexpr ValueTy right() const noexcept {
			return m_downRight.x();
		}

		constexpr ValueTy left() const noexcept {
			return m_topLeft.x();
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