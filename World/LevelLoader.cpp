// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "LevelLoader.h"
#include "IO/Logger/Logger.h"
#include "IO/Message/PlayerWonMessage.h"
#include "IO/Message/NewLevelMessage.h"
#include "Graphics/GameGUI/MessageDialog.h"
#include "Audio/AudioMaster.h"
#include "GlobalSettings.h"

void LevelLoader::loadLevel(const WorldLevelId id) {
	saveLevel();

	io::Logger::info("LevelLoader: loading new level - " + std::string(id.toString()));

	m_world.generate(id);
	if (m_resetPlayer) {
		m_player = Player(m_world);
	} else {
		m_player.setPos({ 0.5f, 0.5f });
	}

	io::Logger::message(io::NewLevelMessage(m_world.getActualSize(), m_player.getPos()));

	if (GlobalSettings::get().isTutorialEnabled()) {
		for (const std::string& str : id.getTutorialTexts()) {
			gamegui::MessageDialog::infoMessage("Tutorial", str);
		}
	}

	audio::AudioMaster::setAmbientMusic(audio::AmbienceId::Value(audio::AmbienceId::WORLD_BASIC + id_t(id)));
}

void LevelLoader::loadNextLevel() {
	io::Logger::message(io::PlayerWonMessage(m_player.getStats(), m_player.getHealth()));
	loadLevel(m_world.getLevelId().nextLevelId());
}

void LevelLoader::saveLevel() {
	io::Logger::info("LevelLoader: saving the level - " + std::string(m_world.getLevelId().toString()));

	// TODO: implement
}
