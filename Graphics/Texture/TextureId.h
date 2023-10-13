// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "BasicResourceId.h"

class TextureId : public BasicResourceId {
public:
	enum Value : id_t {
		NO_TEXTURE = 0,

		// Tiles
		STONE_FLOOR,
		STONE_WALL,
		STONE,
		STONE_PORTAL,

		NUMBER_TEXTURE_IDS
	};

public:
	constexpr TextureId() = delete;
	constexpr TextureId(const Value value) noexcept : BasicResourceId(value) {
		assert(value < NUMBER_TEXTURE_IDS);
	}

	constexpr TextureId& operator=(const TextureId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	std::string toString() const override;
	std::string getResourceLocation() const override;
};