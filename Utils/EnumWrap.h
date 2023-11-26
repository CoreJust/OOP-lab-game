// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <cstdint>
#include <concepts>
#include <string_view>

/*
*	EnumWrap.h contains a base class used to wrap some enumeration.
*	
*	It has no appliances as is and must be used to inherit some classes
*	from it.
*/

namespace utils {
	template<std::integral T>
	class EnumWrap {
	protected:
		T m_value;

	public:
		constexpr EnumWrap() noexcept = default;
		constexpr EnumWrap(const EnumWrap&) noexcept = default;
		constexpr EnumWrap(EnumWrap&&) noexcept = default;

		constexpr EnumWrap(const T value) noexcept : m_value(value) { }

		constexpr EnumWrap& operator=(const EnumWrap other) noexcept {
			m_value = T(other);
			return *this;
		}

		constexpr operator T() const noexcept {
			return m_value;
		}

		constexpr explicit operator bool() const noexcept {
			return m_value != 0;
		}

		inline virtual std::string_view toString() const {
			assert(false && "unreachable; EnumWrap::toString() not expected to be called");
			return "";
		}
	};
}