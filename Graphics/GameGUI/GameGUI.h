// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Math/Vector.h"

namespace gamegui {
	// GameGUI's are GUI that is being displayed during GameState
	// Contains a vector of derivatives of both sf::Transformable and sf::Drawable
	class GameGUI {
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