// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "AudioMaster.h"
#include "IO/Logger/Logger.h"

void audio::AudioMaster::init() {
	assert(s_instance == nullptr);

	s_instance = new AudioMaster();
	io::Logger::debug("AudioMaster: initialized");
}

void audio::AudioMaster::destroy() {
	assert(s_instance != nullptr);

	delete s_instance;
	s_instance = nullptr;
	io::Logger::debug("AudioMaster: destroyed");
}

void audio::AudioMaster::setAmbientMusic(const AmbienceId id) {
	assert(s_instance != nullptr);

	s_instance->getAmbience().setTrack(id);
	io::Logger::debug("AudioMaster: ambient music set: " + std::string(id.toString()));
}

void audio::AudioMaster::playSound(const SoundId id) {
	assert(s_instance != nullptr);

	s_instance->getSounds().play(id);
	io::Logger::trace("AudioMaster: sound played: " + std::string(id.toString()));
}
