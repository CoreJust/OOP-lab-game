// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "SettingsMenuState.h"

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>
#include <imgui/imgui_stdlib.h>

#include "IO/Logger/Logger.h"
#include "StateManager.h"
#include "Audio/AudioMaster.h"

SettingsMenuState::SettingsMenuState(StateManager& pManager)
	: State(pManager),
	m_imguiApi("Settings menu", "===  Settings  ===", true, true), 
	m_tmpSets(GlobalSettings::get()) 
{
	io::Logger::trace("SettingsMenuState: initialized");

	audio::AudioMaster::setAmbientMusic(audio::AmbienceId::MENU_MAIN);
}

void SettingsMenuState::freeze() {
	m_display = nullptr; // Destroys the old display, thus returning it to the default state
	m_imguiApi.destroy();
}

void SettingsMenuState::revive() {
	// Does nothing
}

void SettingsMenuState::update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	// Does nothing at the moment
}

void SettingsMenuState::render(sf::RenderWindow& window) {
	if (!m_display) {
		m_display = std::make_unique<Display>(window, true);
		m_tmpSets = GlobalSettings::get();

		m_imguiApi.init(m_display.get());
		m_imguiApi.setCommonButtonWidthForText(" Default ");

		audio::AudioMaster::setAmbientMusic(audio::AmbienceId::MENU_MAIN);
	}

	if (m_imguiApi.tryToBegin(window)) {
		m_imguiApi.setAlignment(Alignment::CENTERED_BY_ELEMENTS);


		// General settings

		m_imguiApi.textSeparator("General settings");
		m_imguiApi.newLine();

		uint32_t choice = m_tmpSets.getDifficulty();
		if (m_imguiApi.comboBox({ "easy", "normal", "hard", "extreme", "nightmarish" }, choice, "Difficulty: ")) {
			m_tmpSets.m_difficulty = Difficulty::Value(choice);
		}

		m_imguiApi.checkBox(m_tmpSets.m_enableTutorials, "Enable tutotial: ");
		m_imguiApi.sliderFloat(m_tmpSets.m_volume, 0.f, 100.f, "Volume: ");
		m_imguiApi.slider<uint32_t>(m_tmpSets.m_updateDistance, 4, 32, "Update distance: ");


		// Graphics settings

		m_imguiApi.newLine();
		m_imguiApi.textSeparator("Graphics settings");
		m_imguiApi.newLine();

		m_imguiApi.slider<uint32_t>(m_tmpSets.m_maxRenderDistance, 4, 32, "Render distance: ");
		m_imguiApi.slider<int32_t>(m_tmpSets.m_fogPower, 0, 4, "Fog power: ");


		// Resources settings

		m_imguiApi.newLine();
		m_imguiApi.textSeparator("Resources settings");
		m_imguiApi.newLine();

		if (m_imguiApi.inputText(m_tmpSets.m_resLocation, "Resources: ")) {
			m_tmpSets.m_texturesLocation = m_tmpSets.m_resLocation + "img/";
			m_tmpSets.m_audioLocation = m_tmpSets.m_resLocation + "audio/";
			m_tmpSets.m_shadersLocation = m_tmpSets.m_resLocation + "shaders/";
			m_tmpSets.m_fontsLocation = m_tmpSets.m_resLocation + "fonts/";
		}

		m_imguiApi.inputText(m_tmpSets.m_textFont, "Font: ");


		// Input settings

		m_imguiApi.newLine();
		m_imguiApi.textSeparator("Input settings");
		m_imguiApi.newLine();

		m_imguiApi.checkBox(m_tmpSets.m_enableVerticalViewMoving, "Enable vertical view moving: ");

		m_imguiApi.inputText(m_tmpSets.m_bindingsFile, "Bindings file: ");

		choice = m_tmpSets.m_inputMode;
		if (m_imguiApi.comboBox({ "keyboard and mouse", "file" }, choice, "Input mode: ")) {
			m_tmpSets.m_inputMode = io::InputMode::Value(choice);
		}

		m_imguiApi.inputText(m_tmpSets.m_inputFile, "Input file: ");
		m_imguiApi.checkBox(m_tmpSets.m_isToSaveInput, "Save input: ");


		// Saving

		m_imguiApi.newLine();
		m_imguiApi.separator();
		m_imguiApi.newLine();

		if (m_imguiApi.button("Save")) {
			GlobalSettings::get() = m_tmpSets;
			GlobalSettings::storeSettings();
		}

		if (m_imguiApi.button("Default")) {
			m_tmpSets = GlobalSettings();
		}

		if (m_imguiApi.button("Back")) {
			m_imguiApi.end();

			m_pManager.popState();

			return;
		}

		m_imguiApi.end();
	} else {
		m_pManager.popState();
	}
}
