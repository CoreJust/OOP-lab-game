// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/BasicId.h"

/*
*	SoundId(.h/.cpp) contains a class that represents the sound effect Id.
*/

namespace audio {
	class SoundId : public BasicId {
	public:
		enum Value : id_t {
			SOUND_CLICK = 0,

			SOUND_POISONING,

			SOUND_TELEPORTATION,
			SOUND_SAINT_SPRINGS_BUFF,

			SOUND_HIT,
			SOUND_SHOCK,
			SOUND_EVIL_SPIRIT_EXPLOSION,

			NUMBER_SOUND_IDS
		};

	public:
		constexpr SoundId() = delete;
		constexpr SoundId(Value value) noexcept : BasicId(value) {
			assert(value < NUMBER_SOUND_IDS);
		}

		constexpr SoundId& operator=(SoundId other) noexcept {
			m_value = id_t(other);

			return *this;
		}

		constexpr explicit operator Value() const noexcept {
			return static_cast<Value>(m_value);
		}

		std::string_view toString() const override;
	};
}