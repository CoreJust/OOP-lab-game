// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cmath>
#include <cstdint>
#include <numbers>
#include <format>

#include <SFML/System/Vector2.hpp> // For convertion to sf::Vector2

#include "Utils/Concepts.h"
#include "Cmath.h"
#include "MathUtils.h"

/*
*	Vector.h contains a class that represents a 2D vector or point.
*
*	It consists of a pair of coordinates of an arithmetic type and allows a number of
*	operations over a vector.
*/

namespace math {
	template<::utils::Arithmetic T>
	class Vector2 final {
	public:
		using ValueTy = T;

		// FloatTy - the corresponding to T floating point type
		using FloatTy = CorrespondingFloat<T>;
		using IntegralTy = CorrespondingInteger<T>;

	private:
		T m_x = 0;
		T m_y = 0;

	public:
		///  Constructors and operators  ///

		constexpr Vector2() noexcept = default;
		constexpr Vector2(const Vector2&) noexcept = default;
		constexpr Vector2(Vector2&&) noexcept = default;

		template<utils::Arithmetic U> requires std::is_nothrow_convertible_v<U, T>
		constexpr Vector2(const U x, const U y) noexcept
			: m_x(static_cast<T>(x)), m_y(static_cast<T>(y)) {

		}

		template<utils::Arithmetic U> requires std::is_nothrow_convertible_v<U, T>
		constexpr Vector2(const U val) noexcept // Constructs a vector with same coordinates
			: m_x(static_cast<T>(val)), m_y(static_cast<T>(val)) {

		}

		constexpr Vector2& operator=(const Vector2& other) noexcept {
			m_x = other.x();
			m_y = other.y();

			return *this;
		}

		constexpr Vector2& operator=(Vector2&& other) noexcept {
			m_x = other.x();
			m_y = other.y();

			return *this;
		}

		constexpr bool operator==(const Vector2& other) const noexcept {
			return m_x == other.x() && m_y == other.y();
		}

		constexpr Vector2 operator-() const {
			static_assert(std::is_signed_v<T>);

			return Vector2(-m_x, -m_y);
		}

		constexpr Vector2 operator+(const Vector2& right) const noexcept {
			return Vector2(m_x + right.x(), m_y + right.y());
		}

		constexpr Vector2 operator+(const T value) const noexcept {
			return Vector2(m_x + value, m_y + value);
		}

		constexpr Vector2 operator-(const Vector2& right) const noexcept {
			return Vector2(m_x - right.x(), m_y - right.y());
		}

		constexpr Vector2 operator-(const T value) const noexcept {
			return Vector2(m_x - value, m_y - value);
		}

		constexpr Vector2 operator*(const T value) const noexcept {
			return Vector2(m_x * value, m_y * value);
		}

		constexpr Vector2 operator/(const T value) const {
			return Vector2(m_x / value, m_y / value);
		}

		constexpr Vector2 operator%(const T value) const noexcept {
			if constexpr (std::is_integral_v<T>) {
				return Vector2(m_x % value, m_y % value);
			} else {
				return Vector2(fmod(m_x, value), fmod(m_y, value));
			}
		}

		constexpr Vector2& operator+=(const Vector2& right) noexcept {
			m_x += right.x();
			m_y += right.y();
			return *this;
		}

		constexpr Vector2& operator+=(const T value) noexcept {
			m_x += value;
			m_y += value;
			return *this;
		}

		constexpr Vector2& operator-=(const Vector2& right) noexcept {
			m_x -= right.x();
			m_y -= right.y();
			return *this;
		}

		constexpr Vector2& operator-=(const T value) noexcept {
			m_x -= value;
			m_y -= value;
			return *this;
		}

		constexpr Vector2& operator*=(const T value) noexcept {
			m_x *= value;
			m_y *= value;
			return *this;
		}

		constexpr Vector2& operator/=(const T value) {
			m_x /= value;
			m_y /= value;
			return *this;
		}

		constexpr Vector2& operator%=(const T value) noexcept {
			if constexpr (std::is_integral_v<T>) {
				m_x %= value;
				m_y %= value;
			} else {
				m_x = fmod(m_x, value);
				m_y = fmod(m_y, value);
			}

			return *this;
		}

		template<utils::Arithmetic U> requires std::is_nothrow_convertible_v<U, T>
		constexpr explicit operator Vector2<U>() const noexcept {
			return Vector2<U>(U(m_x), U(m_y));
		}

		template<utils::Arithmetic U> requires std::is_nothrow_convertible_v<U, T>
		constexpr Vector2<U> to() const noexcept { // Another version of the conversion operator
			return Vector2<U>(U(m_x), U(m_y));
		}

		constexpr sf::Vector2<T> toSfml() const noexcept {
			return sf::Vector2<T>(m_x, m_y);
		}


		///  Methods  ///

		constexpr T dotProduct(const Vector2& other) const noexcept {
			return m_x * other.x() + m_y * other.y();
		}

		constexpr FloatTy cosOfAngleWith(const Vector2& other) const noexcept {
			return dotProduct(other) / (length() * other.length());
		}

		// Angle with the positive direction of Ox
		constexpr FloatTy rotationOX() const noexcept {
			FloatTy result = Cmath::acos(cosOfAngleWith({ 1, 0 }));
			if (m_y < 0) {
				return -result;
			} else {
				return result;
			}
		}

		// Angle with the positive direction of Oy
		constexpr FloatTy rotationOY() const noexcept {
			FloatTy result = Cmath::acos(cosOfAngleWith({ 0, 1 }));
			if (m_x > 0) {
				return -result;
			} else {
				return result;
			}
		}

		// Angle with the negative direction of Ox
		constexpr FloatTy rotationNegOX() const noexcept {
			FloatTy result = Cmath::acos(cosOfAngleWith({ -1, 0 }));
			if (m_y > 0) {
				return -result;
			} else {
				return result;
			}
		}

		// Angle with the negative direction of Oy
		constexpr FloatTy rotationNegOY() const noexcept {
			FloatTy result = Cmath::acos(cosOfAngleWith({ 0, -1 }));
			if (m_x < 0) {
				return -result;
			} else {
				return result;
			}
		}

		constexpr FloatTy rotation() const noexcept {
			return rotationOX();
		}

		constexpr FloatTy angleWith(const Vector2& other) const {
			FloatTy result = rotation() - other.rotation();

			return MathUtils::encycleInRange<FloatTy, std::numbers::pi_v<FloatTy>>(result);
		}

		constexpr FloatTy length() const {
			return Cmath::sqrt(m_x * m_x + m_y * m_y);
		}

		constexpr FloatTy distance(const Vector2& to) const noexcept {
			return (*this - to).length();
		}

		constexpr Vector2 normalize() const noexcept {
			return *this / length();
		}

		constexpr Vector2 rotate(const float angle) const noexcept {
			const T _cos = Cmath::cos(angle);
			const T _sin = Cmath::sin(angle);

			return Vector2(m_x * _cos - m_y * _sin, m_x * _sin + m_y * _cos);
		}

		// Returns the area of the rectangle ((0, 0) : Vector)
		constexpr T area() const noexcept {
			return m_x * m_y;
		}

		// Returns a vector with swapped coords
		constexpr Vector2 swap() const noexcept {
			return Vector2(m_y, m_x);
		}

		constexpr Vector2 move(const Vector2& offset) const noexcept {
			return *this + offset;
		}

		constexpr Vector2 up(const T offset = 1) const noexcept {
			return Vector2(m_x, m_y - offset);
		}

		constexpr Vector2 down(const T offset = 1) const noexcept {
			return Vector2(m_x, m_y + offset);
		}

		constexpr Vector2 right(const T offset = 1) const noexcept {
			return Vector2(m_x + offset, m_y);
		}

		constexpr Vector2 left(const T offset = 1) const noexcept {
			return Vector2(m_x - offset, m_y);
		}

		constexpr Vector2 mirrorByX() const noexcept {
			return Vector2(-m_x, m_y);
		}

		constexpr Vector2 mirrorByY() const noexcept {
			return Vector2(m_x, -m_y);
		}

		constexpr Vector2 roundFloor() const noexcept {
			return Vector2(Cmath::floor(m_x), Cmath::floor(m_y));
		}

		constexpr Vector2 roundCeil() const noexcept {
			return Vector2(Cmath::ceil(m_x), Cmath::ceil(m_y));
		}

		constexpr Vector2 abs() const noexcept {
			if constexpr (std::is_unsigned_v<T>) {
				return *this;
			} else {
				return Vector2(std::abs(m_x), std::abs(m_y));
			}
		}

		// Is this vector located to the left-up from the vec
		template<bool IsStrict = false>
		constexpr bool isToUpLeftFrom(const Vector2& vec) const noexcept {
			if constexpr (IsStrict) {
				return m_x < vec.x() && m_y < vec.y();
			} else {
				return m_x <= vec.x() && m_y <= vec.y();
			}
		}

		// Is this vector located to the down-right from the vec
		template<bool IsStrict = false>
		constexpr bool isToDownRightFrom(const Vector2& vec) const noexcept {
			if constexpr (IsStrict) {
				return m_x > vec.x() && m_y > vec.y();
			} else {
				return m_x >= vec.x() && m_y >= vec.y();
			}
		}

		std::string toString() const {
			return std::format("({}, {})", m_x, m_y);
		}

		constexpr Vector2 getMaxByXY(const Vector2& vec) const noexcept {
			return Vector2(std::max(m_x, vec.x()), std::max(m_y, vec.y()));
		}

		constexpr Vector2 getMinByXY(const Vector2& vec) const noexcept {
			return Vector2(std::min(m_x, vec.x()), std::min(m_y, vec.y()));
		}
 
		///  Field access  ///

		constexpr T& x() noexcept {
			return m_x;
		}

		constexpr T x() const noexcept {
			return m_x;
		}

		constexpr T& y() noexcept {
			return m_y;
		}

		constexpr T y() const noexcept {
			return m_y;
		}
	};

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int32_t>;
	using Vector2u = Vector2<uint32_t>;
}