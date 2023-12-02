// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "State.h"
#include "MainMenuState.h"
#include "GameState.h"

std::unique_ptr<State> State::makeState(States state, StateManager& pManager) {
	switch (state) {
		case State::MAIN_MENU: return std::make_unique<MainMenuState>(pManager);
		case State::GAME: return std::make_unique<GameState>(pManager);
	default: assert(false && "unreachable"); return nullptr;
	}
}
