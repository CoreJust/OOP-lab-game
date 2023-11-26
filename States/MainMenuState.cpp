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

MainMenuState::MainMenuState(StateManager& pManager) : State(pManager) {
	io::Logger::trace("MainMenuState: initialized");
}

void MainMenuState::freeze() {
	m_display = nullptr; // Destroys the old display, thus returning it to the default state
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

		ImGui::GetIO().FontGlobalScale = 2.f;
		m_display->update(); // So that the graphics can be enabled for ImGui mode
	}

	auto textCentered = [&window](float Y, const char* text) {
		float windowWidth = ImGui::GetWindowSize().x;
		float textWidth = ImGui::CalcTextSize(text).x;

		ImGui::SetCursorPos({ (windowWidth - textWidth) * 0.5f, window.getSize().y * Y });
		ImGui::Text(text);
	};

	ImGui::SFML::SetCurrentWindow(window);

	std::string seedStr = "1";
	if (m_display->isOpen()) {
		ImGui::SetNextWindowPos({ window.getSize().x / 2.f, window.getSize().y / 2.f }, 0, { 0.5f, 0.5f });
		ImGui::Begin("Main menu", nullptr,  ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

		textCentered(0.1f, "===  OOP lab v.5  ===");
		textCentered(0.4f, "Enter the world seed or leave the default:");
		ImGui::NewLine();

		float inputTextStartX = (ImGui::GetWindowContentRegionMax().x - ImGui::CalcItemWidth()) / 2.f;
		ImGui::SetCursorPosX(inputTextStartX);
		if (ImGui::InputText("##", &seedStr, ImGuiInputTextFlags_EnterReturnsTrue)) {
			utils::Seed::setSeed(utils::Seed::fromString(seedStr));
			ImGui::End();

			m_pManager.addState(std::make_unique<GameState>(m_pManager));
			return;
		}

		ImGui::SetCursorPosX(inputTextStartX);
		if (ImGui::Button("Play")) {
			utils::Seed::setSeed(utils::Seed::fromString(seedStr));
			ImGui::End();

			m_pManager.addState(std::make_unique<GameState>(m_pManager));
			return;
		}
		
		ImGui::SameLine();
		ImGui::SetCursorPosX(inputTextStartX + ImGui::CalcItemWidth() - ImGui::CalcTextSize("Quit").x - 8);
		if (ImGui::Button("Quit")) {
			m_pManager.popState();
			ImGui::End();
			return;
		}

		textCentered(0.9f, "by Yegor Ilyin");

		ImGui::End();
		ImGui::EndFrame();

		m_display->clear(sf::Color::Black);
	} else {
		m_pManager.popState();
	}
}
