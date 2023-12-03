// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "MainMenuState.h"

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>
#include <imgui/imgui_stdlib.h>

#include "IO/Logger/Logger.h"
#include "Utils/Seed.h"
#include "StateManager.h"
#include "GameState.h"
#include "Audio/AudioMaster.h"
#include "GlobalSettings.h"

MainMenuState::MainMenuState(StateManager& pManager)
	: State(pManager), 
	m_imguiApi("Main menu", "===  OOP lab v.7  ==="),
	m_difficultyChoice(GlobalSettings::get().getDifficulty())
{
	io::Logger::trace("MainMenuState: initialized");

	audio::AudioMaster::setAmbientMusic(audio::AmbienceId::MENU_MAIN);
}

void MainMenuState::freeze() {
	m_display = nullptr; // Destroys the old display, thus returning it to the default state
	m_imguiApi.destroy();
}

void MainMenuState::revive() {
	// Does nothing - all the required stuff is done in the render() function
}

void MainMenuState::update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	// Does nothing at the moment
}

void MainMenuState::render(sf::RenderWindow& window) {
	if (!m_display) {
		m_display = std::make_unique<Display>(window, true);
		m_seedStr = "1";
		m_difficultyChoice = GlobalSettings::get().getDifficulty();

		m_imguiApi.init(m_display.get());
		m_imguiApi.setCommonButtonWidthForText(" Settings ");

		audio::AudioMaster::setAmbientMusic(audio::AmbienceId::MENU_MAIN);
	}

	if (m_imguiApi.tryToBegin(window)) {
		m_imguiApi.setAlignment(Alignment::CENTERED);

		m_imguiApi.text(0.42f, "");

		if (m_imguiApi.inputText(m_seedStr, "Enter seed: ")) {
			utils::Seed::setSeed(utils::Seed::fromString(m_seedStr));
		}

		if (m_imguiApi.comboBox({ "easy", "normal", "hard", "extreme" }, m_difficultyChoice, "Difficulty: ")) {
			GlobalSettings::get().setDifficulty(Difficulty::Value(m_difficultyChoice));
		}

		m_imguiApi.newLine();
		if (m_imguiApi.button("Play")) {
			m_imguiApi.end();
			m_pManager.setNextState(State::GAME);

			return;
		}

		m_imguiApi.newLine();
		if (m_imguiApi.button("Settings")) {
			m_imguiApi.end();
			m_pManager.setNextState(State::SETTINGS_MENU);

			return;
		}

		m_imguiApi.newLine();
		if (m_imguiApi.button("Info")) {
			m_imguiApi.end();
			m_pManager.setNextState(State::INFO_MENU);

			return;
		}

		m_imguiApi.newLine();
		if (m_imguiApi.button("Quit")) {
			m_imguiApi.end();

			m_pManager.popState();

			return;
		}

		m_imguiApi.text(0.9f, "by Yegor Ilyin");
		m_imguiApi.end();
	} else {
		m_pManager.popState();
	}
}
