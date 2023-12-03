// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "State.h"
#include "Graphics/Display.h"
#include "Graphics/GameGUI/ImGuiApi.h"
#include "GlobalSettings.h"

/*
*	SettingsMenuState.h contains a class that inherits parent class State.
*
*	SettingsMenuState is the state of the settings menu. It is accessible from
*	the main menu and allows to conveniently modify the global settings.
*/

class SettingsMenuState : public State {
private:
	std::unique_ptr<Display> m_display; // Non-owning
	gamegui::ImGuiApi m_imguiApi;

	GlobalSettings m_tmpSets;

public:
	SettingsMenuState(StateManager& pManager);

	void freeze() override;
	void revive() override;

	void update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) override;
	void render(sf::RenderWindow& window) override;
};
