// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Utils/NoNullptr.h"
#include "IO/Input/VirtualInput.h"

/*
*	State(.h/.cpp) contains a base class for all the states.
* 
*	A state if the currently running context, e.g. the running game, the main menu, settings, etc
*/

class StateManager;

// State represents, well, a game menu (or the game itself)
// Manages the game update, GUI, graphics, etc (of course, via the corresponding classes)
// Must be updated every tick
class State {
public:
	enum States : uint8_t {
		MAIN_MENU = 0,
		GAME,

		NUMBER_STATES,
		NONE = NUMBER_STATES
	};

protected:
	StateManager& m_pManager;

public:
	constexpr State(StateManager& pManager) noexcept : m_pManager(pManager) { }
	virtual ~State() = default;

	virtual void freeze() = 0; // When a new state is opened over this one
	virtual void revive() = 0; // When the state was closed and this one becomes active once again

	virtual void update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

public:
	static std::unique_ptr<State> makeState(States state, StateManager& pManager);
};