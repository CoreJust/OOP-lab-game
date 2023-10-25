// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Text.h"
#include <SFML/Graphics/Text.hpp>

#include "TextAdapter.h"

gamegui::Text::Text(const std::string& contents, const math::Rectf& pos, uint32_t textSize, sf::Color color) {
	float textScale = pos.getSize().y() / (GameGUI::DEFAULT_TEXT_SIZE * (std::count(contents.begin(), contents.end(), '\n') + 1));

	sf::Text* text = emplaceDrawable<sf::Text>();
	text->setPosition(pos.topLeft().toSfml());
	text->setFont(TextAdapter::getFont());
	text->setString(contents);
	text->setFillColor(color);
	text->setCharacterSize(textSize);
	text->setScale({ textScale * TextAdapter::X_SCALE_MODIFIER, textScale });
}

void gamegui::Text::setText(const std::string& text) noexcept {
	sf::Text* t = (sf::Text*)m_drawables[0].get();
	t->setString(text);
}

const std::string& gamegui::Text::getText() const noexcept {
	sf::Text* t = (sf::Text*)m_drawables[0].get();
	return t->getString();
}
