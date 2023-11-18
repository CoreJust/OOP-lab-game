// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "State.h"
#include "Graphics/Display.h"

/*
*	MainMenuState.h contains a class that inherits parent class State.
*
*	MainManuState is the state of the main menu. It is the first state to be run
*	and it starts the other states. It uses the alternative rendering scheme with
*	a gamegui module (a wrap over ImGui).
*/

class MainMenuState : public State {
private:
	std::unique_ptr<Display> m_display; // Non-owning

public:
	MainMenuState(StateManager& pManager);

	void freeze() override;
	void revive() override;

	void update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) override;
	void render(sf::RenderWindow& window) override; // Has its own internal cycle
};
