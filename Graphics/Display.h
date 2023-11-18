// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Utils/NoNullptr.h"

/*
*	Display.h contains a class that manages the window.
*
*	It can be used in two modes:
*		1) Owning mode - creates and destroys the window and required contexts
*		2) Non-owning mode - just manages an external window
*/

// Manages the window
class Display final {
private:
	utils::NoNullptr<sf::RenderWindow> m_window;
	sf::Clock m_deltaClock;
	float m_mouseWheelDelta = 0.f;
	bool m_isOpen;
	bool m_isOwning;
	
	// Cannot be accessed from outside
	// Enables some ImGui-specific functions (depends on the vector's back)
	// Made static for synchronization among all the displays (so that non-owning displays work correctly)
	// Note: if several owning displays are to be used in the future (of what I have no plans for the time being),
	//		 than this vector must be divided in several with each attached to its own window (map<...*, vector<bool>> I guess)
	static inline std::vector<bool> s_useImgui { }; 

public:
	Display(uint32_t width, uint32_t height, const sf::String& title, bool useImGui = false); // Owning mode
	Display(sf::RenderWindow& externalWindow, bool useImGui); // Non-owning mode
	~Display();

	void update();
	void pollEvents();
	void clear(const sf::Color& color = sf::Color::White);
	void display();
	void close();

	bool isOpen() const noexcept;

	sf::RenderWindow& getWindow() noexcept;
	float& getMouseWheelDeltaRef() noexcept;

private:
	void updateViewSize();
	void setupImGui();
	void destroyImGui();
};