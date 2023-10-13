// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Player.h"
#include "EntityController.h"

namespace gamegui {
	class ProgressBar;
}

class PlayerContoller final : public EntityController {
private:
	gamegui::ProgressBar* m_healthBar;

public:
	PlayerContoller(std::unique_ptr<Player> player, World& pWorld);

	// Handles player input and controls player
	void update(const float deltaTime, utils::NoNullptr<io::VirtualInput> input) override;

	void draw(RenderMaster& renderMaster) override;

	void initGUI(RenderMaster& renderMaster, Camera& camera);

	Player& getPlayer();
};