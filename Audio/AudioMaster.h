// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Ambience.h"
#include "Sounds.h"

/*
*	AudioMaster(.h/.cpp) contains a class that is responsible
*	for managing sounds. 
*
*	It is similar to the RenderMaster, but the audio module
*	is way simpler. Also, unlike RenderMaster, AudioMaster uses
*	static interface (i.e. Singleton), due to its specifics - 
*	it can be used from almost anywhere.
* 
*	There are 2 kinds of audio: the sound effects are short sounds
*	that are triggered by something, and the ambience is a continuous
*	music that is played in the backround.
*/

namespace audio {
	class AudioMaster final {
	private:
		Ambience m_ambience;
		Sounds m_sounds;

	private:
		inline static AudioMaster* s_instance = nullptr;

	protected:
		AudioMaster() = default;

		constexpr Ambience& getAmbience() noexcept {
			return m_ambience;
		}

		constexpr Sounds& getSounds() noexcept {
			return m_sounds;
		}

	public:
		static void init();
		static void destroy();

		static void setAmbientMusic(const AmbienceId id);
		static void playSound(const SoundId id);
	};
}