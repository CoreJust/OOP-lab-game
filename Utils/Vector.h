#pragma once
#include <cmath>
#include <concepts>
#include <ostream>
#include <format>

namespace utils {
	constexpr float PI = 3.1415926536f; // M_PI is not suitable

	template<class T>
	concept Arithmetic = std::is_arithmetic_v<T>;


	template<Arithmetic T>
	class Vector2 final {
	public:
		// FloatTy - the corresponding to T floating point type
		using FloatTy = std::conditional<sizeof(T) <= sizeof(float), float, double>::type;

	private:
		T m_x = 0;
		T m_y = 0;

	public:
		///  Constructors and operators  ///

		constexpr Vector2() noexcept = default;
		constexpr Vector2(const Vector2&) noexcept = default;
		constexpr Vector2(Vector2&&) noexcept = default;

		template<Arithmetic U> requires std::is_nothrow_convertible_v<U, T>
		constexpr Vector2(U x, U y) noexcept 
			: m_x(static_cast<T>(x)), m_y(static_cast<T>(y)) {

		}

		constexpr Vector2(T x, T y) noexcept
			: m_x(x), m_y(y) {

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

		constexpr Vector2 operator+(T value) const noexcept {
			return Vector2(m_x + value, m_y + value);
		}

		constexpr Vector2 operator-(const Vector2& right) const noexcept {
			return Vector2(m_x - right.x(), m_y - right.y());
		}

		constexpr Vector2 operator-(T value) const noexcept {
			return Vector2(m_x - value, m_y - value);
		}

		constexpr Vector2 operator*(T value) const noexcept {
			return Vector2(m_x * value, m_y * value);
		}

		constexpr Vector2 operator/(T value) const {
			return Vector2(m_x / value, m_y / value);
		}

		constexpr Vector2 operator%(T value) const noexcept {
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

		constexpr Vector2& operator+=(T value) noexcept {
			m_x += value;
			m_y += value;
			return *this;
		}

		constexpr Vector2& operator-=(const Vector2& right) noexcept {
			m_x -= right.x();
			m_y -= right.y();
			return *this;
		}

		constexpr Vector2& operator-=(T value) noexcept {
			m_x -= value;
			m_y -= value;
			return *this;
		}

		constexpr Vector2& operator*=(T value) noexcept {
			m_x *= value;
			m_y *= value;
			return *this;
		}

		constexpr Vector2& operator/=(T value) {
			m_x /= value;
			m_y /= value;
			return *this;
		}

		constexpr Vector2& operator%=(T value) noexcept {
			if constexpr (std::is_integral_v<T>) {
				m_x %= value;
				m_y %= value;
			} else {
				m_x = fmod(m_x, value);
				m_y = fmod(m_y, value);
			}

			return *this;
		}

		template<Arithmetic U> requires std::is_nothrow_convertible_v<U, T>
		constexpr explicit operator Vector2<U>() const {
			return Vector2<U>(U(m_x), U(m_y));
		}

		///  Methods  ///

		constexpr T dotProduct(const Vector2& other) const {
			return m_x * other.x() + m_y * other.y();
		}

		constexpr FloatTy cosOfAngleWith(const Vector2& other) const {
			return dotProduct(other) / (length() * other.length());
		}

		FloatTy angleWith(const Vector2& other) const {
			float result = acos(cosOfAngleWith(other));
			if (result > PI) {
				result -= 2 * PI;
			}

			return result;
		}

		FloatTy length() const {
			return sqrt(m_x * m_x + m_y * m_y);
		}

		constexpr FloatTy distance(const Vector2& to) const {
			return (*this - to).length();
		}

		constexpr Vector2 mirrorByX() const noexcept {
			return Vector2(-m_x, m_y);
		}

		constexpr Vector2 mirrorByY() const noexcept {
			return Vector2(m_x, -m_y);
		}

		constexpr Vector2<int32_t> roundFloor() const noexcept {
			static_assert(std::is_floating_point_v<T>);

			return Vector2<int32_t>(std::floor(m_x), std::floor(m_y));
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
		constexpr bool isToLeftUpFrom(const Vector2& vec) const noexcept {
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

		// Return the vector with members equal to the outputs to the func for the pairs of (x, vec.x) and (y, vec.y)
		template<std::invocable Func>
			requires requires (Func f, T x, T y) { std::is_same_v<f(x, y), x>; }
		constexpr Vector2 invokeForXY(const Vector2& vec, Func func) const {
			return Vector2(func(m_x, vec.x()), func(m_y, vec.y()));
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

	typedef Vector2<float> Vector2f;
	typedef Vector2<int32_t> Vector2i;
	typedef Vector2<uint32_t> Vector2u;
}