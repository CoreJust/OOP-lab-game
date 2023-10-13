// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <memory>

#include "Utils/NoNullptr.h"
#include "IO/VirtualInput.h"
#include "State.h"

class StateManager final {
private:
	std::unique_ptr<io::VirtualInput> m_virtualInput;
	std::vector<std::unique_ptr<State>> m_states;
	bool m_popState = false;
	bool m_isToExit = false;

public:
	StateManager(const float& mouseWheelDelta);

	void update(sf::RenderWindow& window, float deltaTime);

	void addState(std::unique_ptr<State> state);
	void popState();

	utils::NoNullptr<State> getCurrentState() const;
	bool isToBeClosed() const noexcept; // must the program be closed (after the save)
};