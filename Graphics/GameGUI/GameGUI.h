// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Math/Vector.h"

/*
*	GameGUI(.h/.cpp) contains a class that is base to some of the ingame GUIs.
*
*	Unlike those rendered by the ImGui, these ones rely solely on the SFML or the Graphics module.
*	Being the base class, the GameGUI is expected to be used solely via its inheritors.
*/

namespace gamegui {
	// GameGUI's are GUI that is being displayed during GameState
	// Contains a vector of derivatives of both sf::Transformable and sf::Drawable
	class GameGUI {
	public:
		constexpr inline static uint32_t DEFAULT_TEXT_SIZE = 30;

	protected:
		std::vector<std::unique_ptr<sf::Drawable>> m_drawables;

	public:
		void render(sf::RenderWindow& window, const sf::Transform& transform);

		void move(const math::Vector2f& pos);
		void clear();

		template<class T, class... Args>
			requires std::is_base_of_v<sf::Drawable, T> && std::is_base_of_v<sf::Transformable, T>
		T* emplaceDrawable(Args... args) {
			m_drawables.push_back(std::make_unique<T>(std::forward<Args>(args)...));
			return static_cast<T*>(m_drawables.back().get());
		}
	};
}