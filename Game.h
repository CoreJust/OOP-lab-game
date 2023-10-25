// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Utils/Timer.h"
#include "Graphics/Display.h"
#include "States/StateManager.h"

/*
*	Game(.h/.cpp) contains a class that represents the game as application.
*
*	It manages the highest-level logic - runs the game cycle and invokes the methods
*	of the underlying classes (mostly the Display and StateManager).
* 
*	The Game class is where the application's main timer is handled. It starts the whole
*	chain of update and draw/render methods.
*/

// The main cycle
class Game final {
private:
	Display m_display;
	StateManager m_stateManager;

	utils::Timer m_timer;

public:
	Game();

	void run();
};
