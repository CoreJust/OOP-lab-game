#pragma once
#include "Utils/Timer.h"
#include "Graphics/Display.h"
#include "States/StateManager.h"

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