// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "MessageDialog.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include "IO/Logger/Logger.h"
#include "Graphics/Display.h"
#include "Audio/AudioMaster.h"

gamegui::MessageDialog::MessageDialog(const std::string& title, const std::string& text, const std::string& button1, const std::string& button2)
	: m_title(title), m_text(text), m_button1(button1), m_button2(button2) {
	io::Logger::trace("MessageDialog: created with title " + title + " and text " + text);
}

int8_t gamegui::MessageDialog::open() {
	assert(s_window != nullptr);

	return open(*s_window);
}

int8_t gamegui::MessageDialog::open(sf::RenderWindow& window) {
	io::Logger::debug("MessageDialog: opened with title " + m_title);

	Display display(window, true);

	ImGui::GetIO().FontGlobalScale = 2.f;
	ImGui::SFML::SetCurrentWindow(window);

	sf::Clock deltaClock;
	int8_t result = 0;
	while (display.isOpen()) {
		if (deltaClock.getElapsedTime().asMilliseconds() < 1) {
			continue;
		}

		const sf::Time deltaTime = deltaClock.restart();
		display.update();

		ImGui::SetNextWindowPos({ window.getSize().x / 2.f, window.getSize().y / 2.f }, 0, { 0.5f, 0.5f });
		ImGui::Begin(m_title.data(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text(m_text.data());
		ImGui::NewLine();
	
		if (ImGui::Button(m_button1.data())) {
			result = 1;
			display.close();

			audio::AudioMaster::playSound(audio::SoundId::SOUND_CLICK);
			
			io::Logger::debug("MessageDialog: button 1 pressed");
		} else if (!m_button2.empty() && ImGui::Button(m_button2.data())) {
			result = 2;
			display.close();

			audio::AudioMaster::playSound(audio::SoundId::SOUND_CLICK);

			io::Logger::debug("MessageDialog: button 2 pressed");
		}

		ImGui::End();

		display.clear(sf::Color::Black);
		display.display();
	}

	return result;
}

void gamegui::MessageDialog::infoMessage(const std::string& title, const std::string& text) {
	MessageDialog dialog(title, text);
	dialog.open();
}

void gamegui::MessageDialog::initGUI(sf::RenderWindow& window) {
	s_window = &window;

	io::Logger::trace("MessageDialog: initialized GUI (static) with a window");
}
