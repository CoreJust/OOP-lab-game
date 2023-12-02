// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

/*
*	MessageDialog(.h/.cpp) contains a class that implements a message dialog.
*
*	It is similar to the message box, but relies on the ImGui. Unlike the other guis,
*	the MessageDialog is used separately and can be employed anywhere in the code - 
*	a rare case when the Graphics module's contents are used not via the general 
*	RenderMaster's interface.
* 
*	Usage:.
*		MessageDialog dialog(<title>, <message>, <the first button's text>, <the second button's text>);
*		auto choice = dialog.open();
* 
*		// choice would be 1 if the user pressed the first button, 2 if the second, and zero if just closed the dialog.
* 
*	Note: while the dialog is open, the control is completely taken over by it.
*/

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
		static void infoMessage(const std::string& title, const std::string& text);

	public:
		static void initGUI(sf::RenderWindow& window);
	};
}