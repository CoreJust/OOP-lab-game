// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>

/*
*	TextAdapter(.h/.cpp) contains a class that is responsible for
*	the fonts management.
*
*	It uses a singleton and must be explicitely initialized and then destroyed once
*	somewhere on the higher level.
*/

namespace gamegui {
	// Manages the fonts
	// Uses singleton
	class TextAdapter final {
	public:
		constexpr inline static float X_SCALE_MODIFIER = 0.77f; // Allows to fix text stretching

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