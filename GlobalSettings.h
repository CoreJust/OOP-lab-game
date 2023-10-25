// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstdint>
#include <string>

#include "IO/Input/InputMode.h"

/*
*	GlobalSettings(.h/.cpp) contains a class that represents the global game settings.
* 
*	They are:
*		1) Resources locations
*		2) Game settings (e.g. graphics and world)
*		3) Logging settings
*		4) I/O settings
*/

namespace io {
	class GlobalSettingsLoader;
}

// Contains all the global settings of the game: resource locations, graphical settings
// Implements singleton (since we cannot have two different source locations simultaneously)
class GlobalSettings final {
	friend class io::GlobalSettingsLoader;

private:
	std::string m_texturesLocation = "res/img/";
	std::string m_audioLocation = "res/audio/";
	std::string m_shadersLocation = "res/shaders/";
	std::string m_fontsLocation = "res/fonts/";

	std::string m_textFont = "Visitor_Rus";

	uint32_t m_maxRenderDistance = 10;
	uint32_t m_updateDistance = 15;

	io::InputMode m_inputMode = io::KEYBOARD_AND_MOUSE_INPUT;
	std::string m_inputFile = "input_save";
	bool m_isToSaveInput = true;

	bool m_isToLogInput = false;
	bool m_isToLogDeltaTime = false;
	bool m_isToLogSettings = true;
	bool m_isToLogEntitiesPos = false;
	bool m_isToLogEntitiesEffects = true;

private:
	inline static GlobalSettings* s_instance = nullptr;

public:
	static void initSettings(); // will be from a file in the future
	static void destroySettings();

	// Gives access to the instance of the global settings
	static GlobalSettings& get();

public:
	const std::string& getTexturesLocation() const noexcept;
	const std::string& getAudioLocation() const noexcept;
	const std::string& getShadersLocation() const noexcept;
	const std::string& getFontsLocation() const noexcept;

	const std::string& getTextFont() const noexcept;

	uint32_t getMaxRenderDistance() const noexcept;
	uint32_t getUpdateDistance() const noexcept;

	io::InputMode getInputMode() const noexcept;
	const std::string& getInputFile() const noexcept;
	bool isToSaveInput() const noexcept;

	bool isToLogInput() const noexcept;
	bool isToLogDeltaTime() const noexcept;
	bool isToLogSettings() const noexcept;
	bool isToLogEntitiesPos() const noexcept;
	bool isToLogEntitiesEffects() const noexcept;
};