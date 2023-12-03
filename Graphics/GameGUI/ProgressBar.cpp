// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ProgressBar.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "TextAdapter.h"

constexpr float DEFAULT_PROGRESS_BAR_OUTLINE_THICKNESS = 0.008f;

gamegui::ProgressBar::ProgressBar(
	const std::string& name, 
	const math::Rectf& pos, 
	sf::Color color, 
	sf::Color boundingColor, 
	sf::Color textColor
) : m_width(pos.getSize().x()) 
{
	sf::RectangleShape* bar = emplaceDrawable<sf::RectangleShape>(pos.getSize().toSfml());
	bar->setPosition(pos.topLeft().toSfml());
	bar->setFillColor(color);
	bar->setOutlineColor(sf::Color::Transparent);
	bar->setOutlineThickness(DEFAULT_PROGRESS_BAR_OUTLINE_THICKNESS);

	sf::RectangleShape* bounds = emplaceDrawable<sf::RectangleShape>(pos.getSize().toSfml());
	bounds->setPosition(pos.topLeft().toSfml());
	bounds->setFillColor(sf::Color::Transparent);
	bounds->setOutlineColor(boundingColor);
	bounds->setOutlineThickness(DEFAULT_PROGRESS_BAR_OUTLINE_THICKNESS);

	float height = pos.getSize().y();
	float textOffset = height * 0.2f;
	float textScale = (height - textOffset * 2) / GameGUI::DEFAULT_TEXT_SIZE;

	sf::Text* text = emplaceDrawable<sf::Text>();
	text->setPosition((pos.topLeft() + textOffset).toSfml());
	text->setFont(TextAdapter::getFont());
	text->setString(name);
	text->setFillColor(textColor);
	text->setCharacterSize(GameGUI::DEFAULT_TEXT_SIZE);
	text->setScale({ textScale * TextAdapter::X_SCALE_MODIFIER, textScale });
}

void gamegui::ProgressBar::setValue(float val) noexcept {
	if (val != m_value) {
		m_value = val;

		sf::RectangleShape* bar = (sf::RectangleShape*)m_drawables[0].get();
		bar->setSize({ m_width * m_value, bar->getSize().y });
	}
}

float gamegui::ProgressBar::getValue() const noexcept {
	return m_value;
}

void gamegui::ProgressBar::setText(const std::string& text) noexcept {
	sf::Text* t = (sf::Text*)m_drawables[2].get();
	t->setString(text);
}

const std::string& gamegui::ProgressBar::getText() const noexcept {
	sf::Text* t = (sf::Text*)m_drawables[2].get();
	return t->getString();
}
