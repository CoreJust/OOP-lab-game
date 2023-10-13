// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstring>

namespace math {
	// Literally a square array the size of Size x Size
	template<class T, uint32_t Size>
	struct SquareArray final {
		static_assert(Size > 0);

		using ArrayTy = T[Size * Size];


		///  Fields  ///

		ArrayTy data;


		///  Methods  ///

		constexpr SquareArray() noexcept : data{ 0 } { }
		constexpr SquareArray(const SquareArray&) noexcept = default;
		constexpr SquareArray(SquareArray&&) noexcept = default;

		inline SquareArray& operator=(const SquareArray& other) noexcept {
			memcpy(data, other.data, sizeof(ArrayTy));

			return *this;
		}

		inline SquareArray& operator=(SquareArray&& other) noexcept {
			memcpy(data, other.data, sizeof(ArrayTy));

			return *this;
		}

		constexpr T& at(const uint32_t x, const uint32_t y) {
			assert(x < Size && y < Size);

			return data[y * Size + x];
		}

		constexpr const T& at(const uint32_t x, const uint32_t y) const {
			assert(x < Size && y < Size);

			return data[y * Size + x];
		}
	};
}