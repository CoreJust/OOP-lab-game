// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cassert>
#include <cstdint>
#include <string>

using id_t = uint32_t;

// Basic class for all the Ids
class BasicId {
protected:
	id_t m_id;

public:
	constexpr BasicId() = delete;
	constexpr BasicId(const id_t id) noexcept : m_id(id) { }
	constexpr BasicId(const BasicId&) noexcept = default;
	constexpr BasicId(BasicId&&) noexcept = default;

	constexpr BasicId& operator=(const BasicId other) noexcept {
		m_id = other;

		return *this;
	}

	/*
	constexpr bool operator==(const BasicId other) const noexcept {
		return m_id == id_t(other);
	}

	constexpr auto operator<=>(const BasicId other) const noexcept {
		return m_id <=> id_t(other);
	}
	*/

	constexpr operator id_t() const noexcept {
		return m_id;
	}

	constexpr explicit operator bool() const noexcept {
		return m_id != 0;
	}

	inline virtual std::string toString() const {
		assert(false && "unreachable; BasicId::toString() not expected to be called");

		return "";
	}
};