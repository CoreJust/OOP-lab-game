// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>

namespace gamegui {
	// Manages the fonts
	// Uses singleton
	class TextAdapter final {
	private:
		sf::Font m_font;

	private:
		static inline TextAdapter* s_instance = nullptr;

	private:
		TextAdapter(std::string_view fileName);

	public:
		static void initTextAdapter();
		static void destroyTextAdapter();

		static sf::Font& getFont();
	};
}