// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Display.h"

#include <GL/glew.h>
#include <SFML/Window/Event.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include "IO/Logger.h"
#include "Texture/Texture.h"

Display::Display(uint32_t width, uint32_t height, const sf::String& title, bool useImGui)
	: m_isOpen(true), 
	m_isOwning(true),
	m_window(new sf::RenderWindow())
{
	s_useImgui.push_back(useImGui);

	sf::ContextSettings sets;
	sets.majorVersion = 3;
	sets.minorVersion = 3;
	sets.depthBits = 24;
	sets.antialiasingLevel = 4;

	m_window->create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Resize, sets);
	m_window->setVerticalSyncEnabled(true);

	updateViewSize();

	if (useImGui) {
		setupImGui();
	}

	glewExperimental = GL_TRUE;
	if (auto errorCode = glewInit(); errorCode != GLEW_OK) {
		io::Logger::logError("Failed to initialize GLEW: " + std::string((const char*)glewGetErrorString(errorCode)));
		return;
	} else {
		io::Logger::logInfo("GLEW library initialized successfully");
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	io::Logger::logInfo("Initialized display and graphics");
}

Display::Display(sf::RenderWindow& externalWindow, bool useImGui) 
	: m_isOpen(externalWindow.isOpen()), m_isOwning(false), m_window(&externalWindow) {
	s_useImgui.push_back(useImGui);
	updateViewSize();

	if (useImGui && (s_useImgui.size() == 1 || s_useImgui[s_useImgui.size() - 2] == false)) {
		setupImGui();
	}
}

Display::~Display() {
	assert(s_useImgui.size());
	if (s_useImgui.back() && (s_useImgui.size() == 1 || s_useImgui[s_useImgui.size() - 2] == false)) {
		destroyImGui();
	}

	s_useImgui.pop_back();

	if (m_isOpen) {
		if (m_isOwning) {
			m_window->close();
			m_isOpen = false;
		} else { // Non-owning
			m_isOpen = false;
		}
	}

	if (m_isOwning) {
		delete m_window.get();
	}
}

void Display::update() {
	pollEvents();

	if (s_useImgui.back()) {
		const sf::Time deltaTime = m_deltaClock.restart();
		ImGui::SFML::Update(*m_window, deltaTime);
	}
}

void Display::pollEvents() {
	sf::Event event;
	
	while (m_window->pollEvent(event)) {
		if (s_useImgui.back()) {
			ImGui::SFML::ProcessEvent(*m_window, event);
		}

		if (event.type == sf::Event::Closed) {
			close();
			break;
		} else if (event.type == sf::Event::Resized) {
			updateViewSize();
		} else if (event.type == sf::Event::MouseWheelScrolled) {
			m_mouseWheelDelta = event.mouseWheelScroll.delta;
		}
	}
}

void Display::clear(const sf::Color& color) {
	m_window->clear(color);
}

void Display::display() {
	if (s_useImgui.back()) {
		ImGui::SFML::Render(*m_window);
	}

	m_window->display();
}

void Display::close() {
	if (m_isOpen) {
		if (m_isOwning) {
			m_window->close();
			m_isOpen = false;
		} else { // Non-owning
			m_isOpen = false;
		}
	}
}

bool Display::isOpen() const noexcept {
	return m_isOpen;
}

sf::RenderWindow& Display::getWindow() noexcept {
	return *m_window;
}

float& Display::getMouseWheelDeltaRef() noexcept {
	return m_mouseWheelDelta;
}

void Display::updateViewSize() {
	float xViewSize = static_cast<float>(m_window->getSize().x);
	float yViewSize = static_cast<float>(m_window->getSize().y);

	glViewport(0, 0, xViewSize, yViewSize);

	if (xViewSize >= yViewSize) {
		float aspectRatio = xViewSize / yViewSize;
		m_window->setView(sf::View(sf::FloatRect(-aspectRatio, -1, 2 * aspectRatio, 2)));
	} else {
		float raspectRatio = yViewSize / xViewSize;
		m_window->setView(sf::View(sf::FloatRect(-1, -raspectRatio, 2, 2 * raspectRatio)));
	}
}

void Display::setupImGui() {
	m_window->setMouseCursorVisible(true);
	if (!ImGui::SFML::Init(*m_window)) {
		io::Logger::logError("Failed to initialize ImGui");
		return;
	} else {
		io::Logger::logInfo("ImGui library initialized successfully");
	}
}

void Display::destroyImGui() {
	ImGui::SFML::Shutdown();
	m_window->setMouseCursorVisible(false);
}
