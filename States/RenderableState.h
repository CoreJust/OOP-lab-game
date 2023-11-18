// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "State.h"
#include "Graphics/Render/RenderMaster.h"

/*
*	RenderableState.h contains a base class for all the renderable states.
*	It inherits the State class.
*
*	A renderable state is a state that is being rendered to the screen via the common
*	interface (render master).
*/

class RenderableState : public State {
protected:
	RenderMaster m_renderMaster;

public:
	inline RenderableState(StateManager& pManager) : State(pManager) { }
};
