#pragma once
#include <vector>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "State.h"

class StateManager final {
private:
	std::vector<std::unique_ptr<State>> m_menus;
	bool m_popMenu = false;
	bool m_isToExit = false;

public:
	StateManager();

	void update(sf::RenderWindow& window, float deltaTime);

	void addMenu(std::unique_ptr<State> menu);
	void popMenu();

	State* getCurrentMenu() const;
	bool isToBeClosed() const; // must the program be closed (after the save)
};