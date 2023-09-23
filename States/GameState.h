#pragma once
#include "State.h"
#include "Graphics/Camera.h"
#include "Graphics/Render/RenderMaster.h"
#include "World/Entity/PlayerController.h"
#include "World/World.h"

class GameState : public State {
private:
	PlayerContoller m_playerController;
	Camera m_camera;
	World m_world;

	RenderMaster m_renderMaster;

public:
	GameState();

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};