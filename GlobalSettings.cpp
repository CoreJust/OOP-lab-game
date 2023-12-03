// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "GlobalSettings.h"

#include <cassert>

#include "IO/File/GlobalSettingsLoader.h"

void GlobalSettings::initSettings() {
	assert(s_instance == nullptr);

	s_instance = new GlobalSettings();
	io::GlobalSettingsLoader(*s_instance).load();
}

void GlobalSettings::storeSettings() {
	assert(s_instance != nullptr);

	io::GlobalSettingsLoader(*s_instance).store();
}

void GlobalSettings::destroySettings() {
	assert(s_instance != nullptr);

	delete s_instance;
	s_instance = nullptr;
}

GlobalSettings& GlobalSettings::get() {
	assert(s_instance != nullptr);

	return *s_instance;
}

void GlobalSettings::setDifficulty(const Difficulty difficulty) {
	m_difficulty = difficulty;

	io::Logger::info("GlobalSettings: difficulty set to " + std::string(difficulty.toString()));
}

const std::string& GlobalSettings::getTexturesLocation() const noexcept {
	return m_texturesLocation;
}

const std::string& GlobalSettings::getAudioLocation() const noexcept {
	return m_audioLocation;
}

const std::string& GlobalSettings::getShadersLocation() const noexcept {
	return m_shadersLocation;
}

const std::string& GlobalSettings::getFontsLocation() const noexcept {
	return m_fontsLocation;
}

const std::string& GlobalSettings::getTextFont() const noexcept {
	return m_textFont;
}

float GlobalSettings::getVolume() const noexcept {
	return m_volume;
}

Difficulty GlobalSettings::getDifficulty() const noexcept {
	return m_difficulty;
}

uint32_t GlobalSettings::getMaxRenderDistance() const noexcept {
	return m_maxRenderDistance;
}

uint32_t GlobalSettings::getUpdateDistance() const noexcept {
	return m_updateDistance;
}

int32_t GlobalSettings::getFogPower() const noexcept {
	return m_fogPower;
}

bool GlobalSettings::isEnableVerticalViewMoving() const noexcept {
	return m_enableVerticalViewMoving;
}

bool GlobalSettings::isTutorialEnabled() const noexcept {
	return m_enableTutorials;
}

const std::string& GlobalSettings::getBindingsFile() const noexcept {
	return m_bindingsFile;
}

io::InputMode GlobalSettings::getInputMode() const noexcept {
	return m_inputMode;
}

const std::string& GlobalSettings::getInputFile() const noexcept {
	return m_inputFile;
}

bool GlobalSettings::isToSaveInput() const noexcept {
	return m_isToSaveInput;
}

bool GlobalSettings::isToLogInput() const noexcept {
	return m_isToLogInput;
}

bool GlobalSettings::isToLogDeltaTime() const noexcept {
	return m_isToLogDeltaTime;
}

bool GlobalSettings::isToLogSettings() const noexcept {
	return m_isToLogSettings;
}

bool GlobalSettings::isToLogEntitiesPos() const noexcept {
	return m_isToLogEntitiesPos;
}

bool GlobalSettings::isToLogEntitiesEffects() const noexcept {
	return m_isToLogEntitiesEffects;
}
