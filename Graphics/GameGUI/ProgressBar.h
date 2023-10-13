// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include "Math/Rect.h"
#include "GameGUI.h"

namespace gamegui {
	class ProgressBar : public GameGUI {
	private:
		float m_value = 1.f;
		float m_width;

	public:
		ProgressBar(const std::string& name, const math::Rectf& pos, sf::Color color, sf::Color boundingColor, sf::Color textColor = sf::Color::White);

		void setValue(float val) noexcept;
		float getValue() const noexcept;
	};
}