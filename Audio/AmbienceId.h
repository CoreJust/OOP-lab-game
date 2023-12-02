// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"

/*
*	AmbienceId(.h/.cpp) contains a class that represents the ambience music Id.
*/

namespace audio {
	class AmbienceId : public BasicId {
	public:
		enum Value : id_t {
			MENU_MAIN = 0,

			WORLD_BASIC,
			WORLD_MAZE,
			WORLD_SANCTUARY,

			NUMBER_AMBIENCE_IDS
		};

	public:
		constexpr AmbienceId() = delete;
		constexpr AmbienceId(Value value) noexcept : BasicId(value) {
			assert(value < NUMBER_AMBIENCE_IDS);
		}

		constexpr AmbienceId& operator=(AmbienceId other) noexcept {
			m_value = id_t(other);

			return *this;
		}

		constexpr explicit operator Value() const noexcept {
			return static_cast<Value>(m_value);
		}

		std::string_view toString() const override;
	};
}