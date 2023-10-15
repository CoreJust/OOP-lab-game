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

	private:
		static inline sf::RenderWindow* s_window = nullptr;

	public:
		MessageDialog(const std::string& title, const std::string& text);

		void open();
		void open(sf::RenderWindow& window);

	public:
		static void initGUI(sf::RenderWindow& window);
	};
}