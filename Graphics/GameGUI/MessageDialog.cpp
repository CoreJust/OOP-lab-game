// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "MessageDialog.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include "IO/Logger.h"

gamegui::MessageDialog::MessageDialog(const std::string& title, const std::string& text) 
	: m_title(title), m_text(text) {

}

void gamegui::MessageDialog::open() {
	assert(s_window != nullptr);

	open(*s_window);
}

void gamegui::MessageDialog::open(sf::RenderWindow& window) {
	ImGui::GetIO().FontGlobalScale = 2.f;
	ImGui::SFML::SetCurrentWindow(window);

	sf::Clock deltaClock;
	bool isOpen = true;
	while (isOpen) {
		const sf::Time deltaTime = deltaClock.restart();
		ImGui::SFML::Update(window, deltaTime);	

		ImGui::SetNextWindowPos({ window.getSize().x / 2.f, window.getSize().y / 2.f }, 0, { 0.5f, 0.5f });
		ImGui::Begin(m_title.data(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::Text(m_text.data());
		ImGui::NewLine();
	
		if (ImGui::Button("Ok")) {
			isOpen = false;
		}

		ImGui::End();

		ImGui::SFML::Render(window);
		window.display();
	}
}

void gamegui::MessageDialog::initGUI(sf::RenderWindow& window) {
	s_window = &window;
}
