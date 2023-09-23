#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

// State represents, well, a game menu (or the game itself)
// Manages the game update, GUI, graphics, etc (of course, via the corresponding classes)
// Must be updated every tick
class State {
protected:
	State() = default;

public:
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};