// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <type_traits>

#include "Utils/Concepts.h"

// Contains some auxiliary types

namespace math {
	// The CommonType is the type that would be the result of an operation with A and B
	template<class A, class B>
	using CommonType = typename ::std::common_type_t<A, B>;

	// SufficientInteger is an integral type that can contain NumBits bits
	template<uint8_t NumBits>
	using SufficientInteger = ::std::conditional_t<NumBits <= 1, int8_t,
		::std::conditional_t<NumBits <= 2, int16_t,
		::std::conditional_t<NumBits <= 4, int32_t,
		::std::conditional_t<NumBits <= 8, int64_t, ::std::intmax_t>>>>;

	// Unsigned version of the previous type
	template<uint8_t NumBits>
	using SufficientUnsignedInteger = ::std::conditional_t<NumBits <= 1, uint8_t,
		::std::conditional_t<NumBits <= 2, uint16_t,
		::std::conditional_t<NumBits <= 4, uint32_t,
		::std::conditional_t<NumBits <= 8, uint64_t, ::std::uintmax_t>>>>;

	template<utils::Arithmetic T>
	using CorrespondingInteger = ::std::conditional_t<::std::is_integral_v<T>, T, SufficientInteger<sizeof(T)>>;

	template<utils::Arithmetic T>
	using CorrespondingFloat = ::std::conditional_t<::std::is_floating_point_v<T>, T, double>;
}