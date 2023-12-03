// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Ambience.h"

#include <algorithm>
#include "IO/Logger/Logger.h"
#include "GlobalSettings.h"

audio::Ambience::Ambience() 
	: m_currentTrack(AmbienceId::MENU_MAIN) {
	for (id_t id = AmbienceId::Value(0); id < AmbienceId::NUMBER_AMBIENCE_IDS; id++) {
		loadTrack(AmbienceId::Value(id));
	}
}

void audio::Ambience::setTrack(const AmbienceId id) {
	if (id == m_currentTrack) {
		if (m_tracks[id]->getStatus() != sf::SoundSource::Playing) {
			m_tracks[id]->play();
		}

		return;
	}

	m_tracks[m_currentTrack]->stop();
	m_tracks[id]->play();
	m_currentTrack = id;
}

void audio::Ambience::loadTrack(const AmbienceId id) {
	std::string name = std::string(id.toString());
	std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });

	sf::Music& track = *m_tracks.emplace_back(std::make_unique<sf::Music>());
	if (!track.openFromFile(GlobalSettings::get().getAudioLocation() + name + ".ogg")) {
		io::Logger::error("Ambience: failed to load track: " + name);
		return;
	}

	track.setLoop(true);
	track.setVolume(GlobalSettings::get().getVolume());
}
