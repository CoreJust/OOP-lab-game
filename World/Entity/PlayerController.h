// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "Player.h"
#include "EntityController.h"

/*
*	PlayerController(.h/.cpp) contains a class that controls the player.
*
*	Going into detail, it acts as a mediator between the player class and the other
*	game, just as its parent class EntityController does for entities in general.
* 
*	It handles the user input, relaying it to the player, manages the players render
*	(or more specifically provides the necessary information to the render system),
*	and so it does about the GUI related to the player (e.g. player stats).
*/

namespace gamegui {
	class ProgressBar;
	class Text;
}

class PlayerContoller final : public EntityController {
private:
	gamegui::ProgressBar* m_healthBar;
	gamegui::Text* m_infoText;

public:
	PlayerContoller(std::unique_ptr<Player> player, World& pWorld);

	// Handles player input and controls player
	void update(const float deltaTime, utils::NoNullptr<io::VirtualInput> input) override;

	void draw(RenderMaster& renderMaster) override;

	void initGUI(RenderMaster& renderMaster, Camera& camera);

	Player& getPlayer();
};