// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <iterator>
#include "Vector.h"

namespace math {
	template<utils::Arithmetic T>
	class Rect;

	// Allows to iterate through all the positions within a rect
	template<std::integral T>
	class RectIterator final {
	public:
		using value_type = math::Vector2<T>;
		using pointer = const math::Vector2<T>*;
		using reference = const math::Vector2<T>&;
		using difference_type = T;
		using Iterator_category = std::random_access_iterator_tag;

	private:
		math::Vector2<T> m_value;
		T m_xBegin; // the leftmost x in the rect
		T m_xEnd; // the one after the rightmost x in the rect

	private:
		constexpr void next() noexcept {
			if (++m_value.x() == m_xEnd) {
				m_value.x() = m_xBegin;
				++m_value.y();
			}
		}

		constexpr void previous() noexcept {
			if (m_value.x()-- == m_xBegin) {
				m_value.x() = m_xEnd - 1;
				--m_value.y();
			}
		}

		constexpr void advance(int32_t n) noexcept {
			int32_t rowSize = static_cast<int32_t>(m_xEnd - m_xBegin);
			int32_t numRows = (Cmath::abs(n) % rowSize) * Cmath::sgn(n);

			m_value.y() += numRows;
			n -= numRows * rowSize;

			m_value.x() += n;
			if (m_value.x() >= m_xEnd) {
				m_value.x() -= rowSize;
				++m_value.y();
			} else if (m_value.x() < m_xBegin) {
				m_value.x() += rowSize;
				--m_value.y();
			}
		}

	public:
		constexpr RectIterator() noexcept = default;
		constexpr RectIterator(const RectIterator&) noexcept = default;
		constexpr RectIterator(RectIterator&&) noexcept = default;

		constexpr RectIterator(const math::Vector2<T>& pos, T xBegin, T xEnd) noexcept
			: m_value(pos), m_xBegin(xBegin), m_xEnd(xEnd) {
		}

		constexpr RectIterator& operator=(const RectIterator& other) noexcept {
			m_value = other.m_value;
			m_xBegin = other.m_xBegin;
			m_xEnd = other.m_xEnd;

			return *this;
		}

		constexpr RectIterator& operator=(RectIterator&& other) noexcept {
			m_value = other.m_value;
			m_xBegin = other.m_xBegin;
			m_xEnd = other.m_xEnd;

			return *this;
		}

		constexpr bool operator==(const RectIterator& other) const noexcept {
			return m_value == other.m_value;
		}

		constexpr auto operator<=>(const RectIterator& other) const noexcept {
			if (m_value.y() != other.m_value.y()) {
				return m_value.y() <=> other.m_value.y();
			}

			return m_value.x() <=> other.m_value.x();
		}

		constexpr const math::Vector2<T>& operator*() const noexcept {
			return m_value;
		}

		constexpr const math::Vector2<T>* operator->() const noexcept {
			return &m_value;
		}

		constexpr const math::Vector2<T>& operator[](int32_t i) const noexcept {
			return *(*this + i);
		}

		constexpr RectIterator& operator++() noexcept {
			next();
			return *this;
		}

		constexpr RectIterator operator++(int) noexcept {
			RectIterator result = *this;
			next();

			return result;
		}

		constexpr RectIterator& operator--() noexcept {
			previous();
			return *this;
		}

		constexpr RectIterator operator--(int) noexcept {
			RectIterator result = *this;
			previous();

			return result;
		}

		constexpr RectIterator operator+(int32_t n) const noexcept {
			RectIterator tmp = *this;
			tmp.advance(n);

			return tmp;
		}

		constexpr RectIterator operator-(int32_t n) const noexcept {
			RectIterator tmp = *this;
			tmp.advance(-n);

			return tmp;
		}

		constexpr T operator-(const RectIterator& other) const noexcept {
			int32_t rowSize = static_cast<int32_t>(m_xEnd - m_xBegin);

			return (m_value.y() - other.m_value.y()) * rowSize + (m_value.x() - other.m_value.x());
		}

		constexpr RectIterator& operator+=(int32_t n) noexcept {
			advance(n);
			return *this;
		}

		constexpr RectIterator& operator-=(int32_t n) noexcept {
			advance(-n);
			return *this;
		}
	};
}