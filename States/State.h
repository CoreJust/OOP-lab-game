// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Utils/NoNullptr.h"
#include "IO/Input/VirtualInput.h"

class StateManager;

// State represents, well, a game menu (or the game itself)
// Manages the game update, GUI, graphics, etc (of course, via the corresponding classes)
// Must be updated every tick
class State {
protected:
	StateManager& m_pManager;

public:
	constexpr State(StateManager& pManager) noexcept : m_pManager(pManager) { }

	virtual void update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	virtual ~State() = default;
};