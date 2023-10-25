// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

namespace gamegui {
	// Allows to create a message dialog box via ImGui
	class MessageDialog final {
	private:
		std::string m_title;
		std::string m_text;
		std::string m_button1;
		std::string m_button2;

	private:
		static inline sf::RenderWindow* s_window = nullptr;

	public:
		MessageDialog(const std::string& title, const std::string& text, const std::string& button1 = "Ok", const std::string& button2 = "");

		// Returns the exit variant (0 - anything but the button, 1 - first button, 2 - second button)
		int8_t open();
		int8_t open(sf::RenderWindow& window);

	public:
		static void initGUI(sf::RenderWindow& window);
	};
}