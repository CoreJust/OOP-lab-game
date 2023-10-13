// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <ostream>

#include "Concepts.h"

namespace utils {
	// Can be either true, false, or None
	class Tribool final {
	private:
		int8_t m_state;

	public:
		enum class Value : int8_t {
			NONE = -1,
			FALSE = 0,
			TRUE = 1
		};

	public:
		constexpr static Value None = Value::NONE;

	public:
		constexpr Tribool() noexcept : m_state(int8_t(None)) { }
		constexpr Tribool(bool val) noexcept : m_state(val) { }
		constexpr Tribool(Value val) noexcept : m_state(int8_t(val)) { }
		constexpr Tribool(const Tribool& other) noexcept : m_state(other.m_state) { }
		constexpr Tribool(Tribool&& other) noexcept : m_state(other.m_state) { }

		constexpr Tribool& operator=(const Tribool& other) noexcept {
			m_state = other.m_state;
			return *this;
		}

		constexpr Tribool& operator=(Tribool&& other) noexcept {
			m_state = other.m_state;
			return *this;
		}

		constexpr Tribool operator==(Tribool other) const noexcept {
			if (m_state < 0 || other.m_state < 0) {
				return None;
			}

			return m_state == other.m_state;
		}

		constexpr std::partial_ordering operator<=>(Tribool other) const noexcept {
			if (m_state < 0 || other.m_state < 0) {
				return std::partial_ordering::unordered;
			}

			return m_state <=> other.m_state;
		}

		constexpr Tribool operator!() const noexcept {
			if (m_state < 0) {
				return *this;
			}

			return Tribool(!m_state);
		}

		constexpr operator bool() const noexcept {
			return m_state > 0;
		}

		constexpr explicit operator int() const noexcept {
			return m_state;
		}

		template<class T, utils::Callable<T> FuncInCaseTrue, utils::Callable<T> FuncInCaseFalse, utils::Callable<T> FuncInCaseNone>
		constexpr T choose(FuncInCaseTrue funcTrue, FuncInCaseFalse funcFalse, FuncInCaseNone funcNone) const {
			switch (m_state) {
				case 0: return funcFalse();
				case 1: return funcTrue();
			default: return funcNone();
			}
		}

		template<class T>
		constexpr const T& choose(const T& caseTrue, const T& caseFalse, const T& caseNone) const {
			switch (m_state) {
				case 0: return caseFalse;
				case 1: return caseTrue;
			default: return caseNone;
			}
		}

		// Returns the noneValue if tribool is none and tribool otherwise
		constexpr bool toBool(bool noneValue) const noexcept {
			return m_state < 0 ? noneValue : m_state;
		}

		constexpr std::string toString() const noexcept {
			return choose<std::string>("true", "false", "none");
		}

		constexpr Value getValue() const noexcept {
			return static_cast<Value>(m_state);
		}
	};
}