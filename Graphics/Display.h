// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

// Manages the window
class Display final {
private:
	sf::RenderWindow m_window;
	float m_mouseWheelDelta;

public:
	Display(uint32_t width, uint32_t height, std::string title);
	~Display();

	void pollEvents();
	void clear(const sf::Color& color = sf::Color::White);
	void display();

	bool isOpen() const noexcept;

	sf::RenderWindow& getWindow() noexcept;
	float& getMouseWheelDeltaRef() noexcept;

private:
	void updateViewSize();
};