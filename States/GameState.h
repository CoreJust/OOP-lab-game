// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "RenderableState.h"
#include "Graphics/Camera.h"
#include "World/Entity/PlayerController.h"
#include "World/World.h"

/*
*	GameState.h contains a class that inherits parent class RenderableState.
*
*	GameState is the state of the very game - it implements the gameplay, manages
*	the resources related to the game (such as the world and player).
*/

class GameState : public RenderableState {
private:
	World m_world;
	PlayerContoller m_playerController;
	Camera m_camera;

public:
	GameState(StateManager& pManager);

	void freeze() override;
	void revive() override;

	void update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) override;
	void render(sf::RenderWindow& window) override;

public:
	void processPlayerDeath();
};