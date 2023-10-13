// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"
#include "EntityStats.h"

class EntityId : public BasicId {
public:
	enum Value : id_t {
		PLAYER = 0,

		NUMBER_ENTITY_IDS
	};

public:
	constexpr EntityId() = delete;
	constexpr EntityId(Value value) noexcept : BasicId(value) {
		assert(value < NUMBER_ENTITY_IDS);
	}

	constexpr EntityId& operator=(EntityId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	const EntityStats& getEntityStats() const;

	std::string toString() const override;
};