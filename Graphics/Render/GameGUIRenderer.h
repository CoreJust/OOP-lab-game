// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>

#include "Graphics/GameGUI/GameGUI.h"
#include "Graphics/Camera.h"

// Unlike other Renderers, GameGUIRenderer does not need to reupload its contents every tick
// All you need to do is just once register the GUI and then once delete it
// To access GUI's you need a pointer returned by registerGameGUI()
class GameGUIRenderer final {
private:
	std::vector<std::unique_ptr<gamegui::GameGUI>> m_guis;

public:
	template<class T, class... Args>
	T* registerGameGUI(Args... args) {
		m_guis.push_back(std::make_unique<T>(std::forward<Args>(args)...));

		return static_cast<T*>(m_guis.back().get());
	}

	void eraseGameGUI(gamegui::GameGUI* gui);

	void render(sf::RenderWindow& window, Camera& camera);
};