// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Display.h"

#include <GL/glew.h>
#include <SFML/Window/Event.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include "IO/Logger.h"
#include "Texture/Texture.h"

Display::Display(uint32_t width, uint32_t height, std::string title) : m_isOpen(true) {
	sf::ContextSettings settings;
	sf::VideoMode videoMode = sf::VideoMode(width, height);
	uint32_t style = sf::Style::Close | sf::Style::Resize;

	m_window.create(std::move(videoMode), std::move(title), style, std::move(settings));
	m_window.setVerticalSyncEnabled(true);

	updateViewSize();

	if (!ImGui::SFML::Init(m_window)) {
		io::Logger::logError("Failed to initialize ImGui");
		 return;
	} else {
		io::Logger::logInfo("ImGui library initialized successfully");
	}

	if (auto errorCode = glewInit(); errorCode != GLEW_OK) {
		io::Logger::logError("Failed to initialize GLEW: " + std::string((const char*)glewGetErrorString(errorCode)));
		return;
	} else {
		io::Logger::logInfo("GLEW library initialized successfully");
	}

	io::Logger::logInfo("Initialized display and graphics");
}

Display::~Display() {
	if (m_isOpen) {
		ImGui::SFML::Shutdown();
		m_window.close();
		m_isOpen = false;
	}
}

void Display::pollEvents() {
	sf::Event event;
	
	while (m_window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(m_window, event);

		if (event.type == sf::Event::Closed) {
			m_window.close();
		} else if (event.type == sf::Event::Resized) {
			updateViewSize();
		} else if (event.type == sf::Event::MouseWheelScrolled) {
			m_mouseWheelDelta = event.mouseWheelScroll.delta;
		}
	}
}

void Display::clear(const sf::Color& color) {
	m_window.clear(color);
}

void Display::display() {
	m_window.display();
}

void Display::close() {
	if (m_isOpen) {
		ImGui::SFML::Shutdown();
		m_window.close();
		m_isOpen = false;
	}
}

bool Display::isOpen() const noexcept {
	return m_window.isOpen();
}

sf::RenderWindow& Display::getWindow() noexcept {
	return m_window;
}

float& Display::getMouseWheelDeltaRef() noexcept {
	return m_mouseWheelDelta;
}

void Display::updateViewSize() {
	float xViewSize = static_cast<float>(m_window.getSize().x);
	float yViewSize = static_cast<float>(m_window.getSize().y);

	if (xViewSize >= yViewSize) {
		float aspectRatio = xViewSize / yViewSize;
		m_window.setView(sf::View(sf::FloatRect(-aspectRatio, -1, 2 * aspectRatio, 2)));
	} else {
		float raspectRatio = yViewSize / xViewSize;
		m_window.setView(sf::View(sf::FloatRect(-1, -raspectRatio, 2, 2 * raspectRatio)));
	}
}
