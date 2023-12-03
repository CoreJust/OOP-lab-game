// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include "Math/Rect.h"
#include "GameGUI.h"

/*
*	ProgressBar(.h/.cpp) contains a class that inherits GameGUI
*	and implements, well, a progress bar.
*
*	It is actually a colored rectangle filled to some degree and with a text inside.
*/

namespace gamegui {
	class ProgressBar : public GameGUI {
	private:
		float m_value = 1.f;
		float m_width;

	public:
		ProgressBar(const std::string& name, const math::Rectf& pos, sf::Color color, sf::Color boundingColor, sf::Color textColor = sf::Color::White);

		void setValue(float val) noexcept;
		float getValue() const noexcept;

		void setText(const std::string& text) noexcept;
		const std::string& getText() const noexcept;
	};
}