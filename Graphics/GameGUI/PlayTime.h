// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Graphics/Text.hpp>
#include "Utils/Timer.h"
#include "Text.h"

/*
*	PlayTime(.h/.cpp) contains a class that inherits GameGUI
*	and implements a timer of the current time in the game and
*	on the current level.
*/

namespace gamegui {
	class PlayTime final : public Text {
	private:
		utils::Timer m_timer;

	public:
		PlayTime(const math::Vector2f& pos);

		void reset();
		void update();
	};
}