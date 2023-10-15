// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"
#include "Math/Vector.h"

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
	constexpr WorldLevelId(Value value) noexcept : BasicId(value) {
		assert(value < NUMBER_WORLD_LEVEL_IDS);
	}

	constexpr WorldLevelId& operator=(WorldLevelId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	void loadGenerationSettingsTo(WorldGenerationMaster& generationMaster) const;

	math::Vector2i getWorldSize() const noexcept;

	std::string toString() const override;
};