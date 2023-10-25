// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "State.h"
#include "Graphics/Camera.h"
#include "Graphics/Render/RenderMaster.h"
#include "World/Entity/PlayerController.h"
#include "World/World.h"

class GameState : public State {
private:
	World m_world;
	PlayerContoller m_playerController;
	Camera m_camera;

	RenderMaster m_renderMaster;

public:
	GameState(StateManager& pManager);

	void update(float deltaTime, utils::NoNullptr<io::VirtualInput> input) override;
	void render(sf::RenderWindow& window) override;

public:
	void processPlayerDeath();
};