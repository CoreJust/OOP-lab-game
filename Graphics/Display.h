#pragma once
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

// Manages the window
class Display final {
private:
	sf::RenderWindow m_window;

public:
	Display(uint32_t width, uint32_t height, std::string title);
	~Display();

	void pollEvents();
	void clear(const sf::Color& color = sf::Color::White);
	void display();

	bool isOpen() const;

	sf::RenderWindow& getWindow();

private:
	void updateViewSize();
};