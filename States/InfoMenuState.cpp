// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "InfoMenuState.h"

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>
#include <imgui/imgui_stdlib.h>

#include "IO/Logger/Logger.h"
#include "StateManager.h"
#include "Audio/AudioMaster.h"

InfoMenuState::InfoMenuState(StateManager& pManager)
	: State(pManager),
	m_imguiApi("Info menu", "===  About  ===", true, true) {
	io::Logger::trace("InfoMenuState: initialized");

	audio::AudioMaster::setAmbientMusic(audio::AmbienceId::MENU_MAIN);
}

void InfoMenuState::freeze() {
	m_display = nullptr; // Destroys the old display, thus returning it to the default state
	m_imguiApi.destroy();
}

void InfoMenuState::revive() {
	// Does nothing
}

void InfoMenuState::update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) {
	// Does nothing at the moment
}

void InfoMenuState::render(sf::RenderWindow& window) {
	if (!m_display) {
		m_display = std::make_unique<Display>(window, true);

		m_imguiApi.init(m_display.get());

		audio::AudioMaster::setAmbientMusic(audio::AmbienceId::MENU_MAIN);
	}

	if (m_imguiApi.tryToBegin(window)) {
		m_imguiApi.setAlignment(Alignment::CENTERED);

		m_imguiApi.text(
			"Welcome to the OOP game!\n"\
			"\n"\
			"Here you have to pass game levels.\n"\
			"To go to the next level you have to find a golden portal.\n"\
			"At the same time, you need to escape from the enemies.\n"\
			"\n"\
			"This project contains:\n"\
			"\t17 790 lines of code\n"\
			"\t263 source code files\n"\
			"\t161 classes\n"\
			"\n"\
			"List of used resources:\n"\
			"\tC++20 language and Microsoft Visual studio as IDE\n"\
			"\tLibraries: GLEW (OpenGL), GLM, SFML, Dear ImGui for SFML\n"\
			"\tFor creating textures: GIMP\n"\
			"\tMusic and sounds were taken from: freesound.org\n"\
			"\n"\
			"Author: Ilyin Yegor, student of ETU \"LETI\", FCST, group 2303.\n"\
			"Made in 2023."
		);


		// Quitting

		m_imguiApi.newLine();
		m_imguiApi.separator();
		m_imguiApi.newLine();

		if (m_imguiApi.button(" Back  ")) {
			m_imguiApi.end();

			m_pManager.popState();

			return;
		}

		m_imguiApi.end();
	} else {
		m_pManager.popState();
	}
}
