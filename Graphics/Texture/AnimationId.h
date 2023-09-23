#pragma once
#include "BasicResourceId.h"

class AnimationId : public BasicResourceId {
public:
	enum Value : id_t {
		PLAYER = 0,

		NUMBER_ANIMATION_IDS
	};

public:
	constexpr AnimationId() = delete;
	constexpr AnimationId(Value value) noexcept : BasicResourceId(value) { }

	constexpr AnimationId& operator=(AnimationId other) noexcept {
		m_id = id_t(other);

		return *this;
	}

	constexpr explicit operator Value() const noexcept {
		return static_cast<Value>(m_id);
	}

	std::string toString() const override;
	std::string getResourceLocation() const override;
};