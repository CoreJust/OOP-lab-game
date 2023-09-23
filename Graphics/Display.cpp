#include "Display.h"

#include <SFML/Window/Event.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include "Texture/Texture.h"

Display::Display(uint32_t width, uint32_t height, std::string title) {
	sf::ContextSettings settings;
	sf::VideoMode videoMode = sf::VideoMode(width, height);
	uint32_t style = sf::Style::Close | sf::Style::Resize;

	m_window.create(std::move(videoMode), std::move(title), style, std::move(settings));
	m_window.setVerticalSyncEnabled(true);

	updateViewSize();

	ImGui::SFML::Init(m_window);
}

Display::~Display() {
	ImGui::SFML::Shutdown();
	m_window.close();
}

void Display::pollEvents() {
	sf::Event event;
	
	while (m_window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(m_window, event);

		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
			m_window.close();
		} else if (event.type == sf::Event::Resized) {
			updateViewSize();
		}
	}
}

void Display::clear(const sf::Color& color) {
	m_window.clear(color);
}

void Display::display() {
	m_window.display();
}

bool Display::isOpen() const {
	return m_window.isOpen();
}

sf::RenderWindow& Display::getWindow() {
	return m_window;
}

void Display::updateViewSize() {
	float xViewSize = m_window.getSize().x / 10.f;
	float yViewSize = m_window.getSize().y / 10.f;
	sf::View view(sf::FloatRect(-xViewSize, -yViewSize, xViewSize * 2, yViewSize * 2));

	view.move({ 0, Texture::TEXTURE_SIZE });
	m_window.setView(view);
}
