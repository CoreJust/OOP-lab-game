// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <memory>

#include "Utils/NoNullptr.h"
#include "IO/Input/VirtualInput.h"
#include "State.h"

/*
*	StateManager(.h/.cpp) contains a class that manages the states.
*
*	It acts as an intermediator between the highest-level logic
*	and the states.
*	
*	The class contains the input class and a stack (actually, a vector) of
*	states where the topmost is the active one.
* 
*	The general usage scheme:
*		1) At some moment (initially, in the class's constructor)
*		   a state is pushed to it:
* 
*		   StateManager manager(...);
*		   manager.addState(std::make_unique<...>(...));
* 
*		2) Then the manager is updated at every frame. The update of the manager
*		   invokes the corresponding updates and renderings of the state:
* 
*		   manager.update(...);
* 
*		3) Finally, at some moment, the state is changed (which is expected
*		   to be triggered by the currently active state) by pushing another state
*		   or destructing the current:
* 
*		   manager.popState();
* 
*		4) After the a state is popped, the manager loads the previous state and runs it.
*		   If there is no the previous state, than the manager sets the flag to exit
*		   and does nothing. The flag must be checked on the higher level and the game 
*		   is expected to be shut down.
*/

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