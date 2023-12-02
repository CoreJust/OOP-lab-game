// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <memory>
#include <vector>
#include <SFML/Audio/Music.hpp>
#include "AmbienceId.h"

/*
*	Ambience(.h/.cpp) contains a class that is responsible
*	for ambient sounds - the music.
*/

namespace audio {
	class Ambience final {
	private:
		std::vector<std::unique_ptr<sf::Music>> m_tracks;
		AmbienceId m_currentTrack;

	public:
		Ambience();

		void setTrack(const AmbienceId id);

		constexpr AmbienceId getTrack() const noexcept {
			return m_currentTrack;
		}

	private:
		void loadTrack(const AmbienceId id);
	};
}