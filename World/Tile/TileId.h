// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

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
		STONE_PORTAL,
		NEXT_LEVEL_PORTAL,

		SAINT_SPRINGS,
		POISON_CLOUD,


		NUMBER_TILE_IDS
	};

public:
	constexpr TileId() = delete;
	constexpr TileId(Value value) noexcept : BasicId(value) {
		assert(value < NUMBER_TILE_IDS);
	}

	constexpr TileId& operator=(TileId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	const TileInfo& getTileInfo() const;
	TextureId getTileTexture() const;
	TileCategory getCategory() const;

	bool isBackground() const;
	bool isForeground() const;

	std::string toString() const override;
};