// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"
#include "Graphics/Model/TextureCoords.h"
#include "TileInfo.h"

/*
*	TileId(.h/.cpp) contains a class that represents an Id of a Tile.
*
*	Tile id sets the tiles basic qualities (described in the TileInfo.h) and
*	out of them only the passabality is available for modification.
*/

namespace model {
	class ModelDescription;
}

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
		m_value = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_value);
	}

	const TileInfo& getTileInfo() const;
	TileCategory getCategory() const;
	const model::ModelDescription& getModelDescription() const;
	model::TextureCoords& loadToTexCoords(model::TextureCoords& texCoords) const;

	bool isBackground() const;
	bool isForeground() const;

	std::string_view toString() const override;
};