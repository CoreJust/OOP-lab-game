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

		NUMBER_TEXTURE_IDS
	};

public:
	constexpr TextureId() = delete;
	constexpr TextureId(Value value) noexcept : BasicResourceId(value) { }

	constexpr TextureId& operator=(TextureId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	std::string toString() const override;
	std::string getResourceLocation() const override;
};