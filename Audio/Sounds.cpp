// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Sounds.h"

#include <algorithm>
#include "IO/Logger/Logger.h"
#include "GlobalSettings.h"

audio::Sounds::Sounds() {
	m_buffers.reserve(SoundId::NUMBER_SOUND_IDS);
	m_sounds.reserve(SoundId::NUMBER_SOUND_IDS);

	for (id_t id = SoundId::Value(0); id < SoundId::NUMBER_SOUND_IDS; id++) {
		loadSound(SoundId::Value(id));
	}
}

void audio::Sounds::play(const SoundId id) {
	m_sounds[id].play();
}

void audio::Sounds::loadSound(const SoundId id) {
	std::string name = std::string(id.toString());
	std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });

	sf::SoundBuffer& buffer = m_buffers.emplace_back();
	if (!buffer.loadFromFile(GlobalSettings::get().getAudioLocation() + name + ".wav")) {
		io::Logger::error("Sounds: failed to load sound: " + name);
		return;
	}

	sf::Sound& sound = m_sounds.emplace_back(buffer);
	sound.setVolume(GlobalSettings::get().getVolume());
}
