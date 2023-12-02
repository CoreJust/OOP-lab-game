// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "SoundId.h"

/*
*	Sounds(.h/.cpp) contains a class that is responsible
*	for sound effects.
*/

namespace audio {
	class Sounds final {
	private:
		std::vector<sf::SoundBuffer> m_buffers;
		std::vector<sf::Sound> m_sounds;

	public:
		Sounds();

		void play(const SoundId id);

	private:
		void loadSound(const SoundId id);
	};
}