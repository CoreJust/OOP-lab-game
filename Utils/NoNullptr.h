// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>

namespace utils {
	// A wrapper over a pointer to make sure it is not nullptr
	// Doesn't manage pointer allocation/deallocation and is expected to be just a temporary storage
	template<class T>
	class NoNullptr final {
	private:
		T* m_ptr;

	public:
		NoNullptr() = delete;
		constexpr NoNullptr(const NoNullptr& other) noexcept = default;
		constexpr NoNullptr(NoNullptr&& other) noexcept = default;
		constexpr NoNullptr(T* ptr) : m_ptr(ptr) {
			assert(m_ptr != nullptr);
		}

		constexpr NoNullptr& operator=(const NoNullptr& other) noexcept {
			m_ptr = other.m_ptr;

			return *this;
		}

		constexpr NoNullptr& operator=(NoNullptr&& other) noexcept {
			m_ptr = other.m_ptr;

			return *this;
		}

		constexpr T& operator*() {
			return *m_ptr;
		}

		constexpr const T& operator*() const {
			return *m_ptr;
		}

		constexpr T* operator->() {
			return m_ptr;
		}

		constexpr const T* operator->() const {
			return m_ptr;
		}

		constexpr T& operator[](const size_t i) {
			return m_ptr[i];
		}

		constexpr const T& operator[](const size_t i) const {
			return m_ptr[i];
		}

		constexpr T* get() noexcept {
			return m_ptr;
		}
	};
}