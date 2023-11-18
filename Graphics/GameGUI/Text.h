// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include "Math/Rect.h"
#include "GameGUI.h"

/*
*	Text(.h/.cpp) contains a class that inherits GameGUI
*	and implements a simple text label.
*/

namespace gamegui {
	class Text : public GameGUI {
	public:
		Text(
			const std::string& contents, 
			const math::Rectf& pos, 
			uint32_t textSize = GameGUI::DEFAULT_TEXT_SIZE, 
			sf::Color color = sf::Color::White
		);

		void setText(const std::string& text) noexcept;
		const std::string& getText() const noexcept;
	};
}