#pragma once
#include "Utils/BasicId.h"
#include "Graphics/Texture/TextureId.h"
#include "TileInfo.h"

class TileId : public BasicId {
public:
	enum Value : id_t {
		EMPTINESS = 0,

		// Floors
		STONE_FLOOR,

		// Walls
		STONE_WALL,

		// Objects
		STONE,

		// Interactive tiles


		NUMBER_TILE_IDS
	};

public:
	constexpr TileId() = delete;
	constexpr TileId(Value value) noexcept : BasicId(value) { }

	constexpr TileId& operator=(TileId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	const TileInfo& getTileInfo() const;
	TextureId getTileTexture() const;

	std::string toString() const override;
};