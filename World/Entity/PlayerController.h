#pragma once
#include "Player.h"
#include "EntityController.h"

class PlayerContoller final : public EntityController {
public:
	PlayerContoller(std::unique_ptr<Player> player, World* pWorld);

	// Handles player input and controls player
	void update(float deltaTime) override;

	Player& getPlayer();
};