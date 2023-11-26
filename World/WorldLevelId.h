// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"
#include "Math/Vector.h"

/*
*	WorldLevelId(.h/.cpp) contains a class that represents the game level.
* 
*	The whole game process is split into levels - separate worlds with their own
*	settings, goals, enemies, etc. Each level is identified with this class and
*	via it the level's settings can be retrieved.
*/

class WorldGenerationMaster;

// World level Id contains information about default worlds in different levels
class WorldLevelId final : public BasicId {
public:
	enum Value : id_t {
		BASIC_LEVEL = 0,
		SANCTUARY_LEVEL,

		NUMBER_WORLD_LEVEL_IDS
	};

public:
	constexpr WorldLevelId() = delete;
	constexpr WorldLevelId(const Value value) noexcept : BasicId(value) {
		assert(value < NUMBER_WORLD_LEVEL_IDS);
	}

	constexpr WorldLevelId& operator=(const WorldLevelId other) noexcept {
		m_value = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_value);
	}

	void loadGenerationSettingsTo(WorldGenerationMaster& generationMaster) const;

	math::Vector2i getWorldSize() const noexcept;

	std::string_view toString() const override;
};