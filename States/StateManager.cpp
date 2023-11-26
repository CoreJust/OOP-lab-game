// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "StateManager.h"

#include "IO/Input/KeyboardMouseInput.h"
#include "IO/Logger/Logger.h"
#include "Graphics/GameGUI/MessageDialog.h"
#include "GlobalSettings.h"
#include "MainMenuState.h"
#include "GameState.h"

StateManager::StateManager(const float& mouseWheelDelta)
	: m_virtualInput(io::VirtualInput::makeVirtualInput(GlobalSettings::get().getInputMode(), mouseWheelDelta)) {
	io::Logger::trace("StateManager: initialized");

	addState(std::make_unique<MainMenuState>(*this));
}

void StateManager::update(sf::RenderWindow& window, float deltaTime) {
	if (m_virtualInput->update(deltaTime)) { // deltaTime can be changed here!
		io::Logger::debug("StateManager: input file ended, reloading input in keyboard/mouse mode...");

		const float& mouseWheelDelta = m_virtualInput->getMouseWheelDeltaRef();
		m_virtualInput.reset();
		m_virtualInput = io::VirtualInput::makeVirtualInput(io::InputMode::KEYBOARD_AND_MOUSE_INPUT, mouseWheelDelta);
	}

	if (GlobalSettings::get().isToLogDeltaTime()) {
		io::Logger::trace("StateManager: update with deltaTime: " + std::to_string(deltaTime));
	}

	if (m_virtualInput->isKeyPressed(io::Key::KEY_ESCAPE)) {
		gamegui::MessageDialog dialog("Game message", "Wanna quit?", "No way!", "Quit");
		if (dialog.open() == 2) { // Quit
			io::Logger::debug("StateManager: quitting the current state...");
			popState();
		}
	}

	getCurrentState()->update(deltaTime, m_virtualInput.get());
	getCurrentState()->render(window);

	if (m_popState) {
		m_popState = false;
		m_states.pop_back();

		m_isToExit = m_states.size() == 0;
		if (!m_isToExit) {
			m_states.back()->revive();
		}

		io::Logger::trace("StateManager: state popped, states left " + std::to_string(m_states.size()));
	}
}

void StateManager::addState(std::unique_ptr<State> state) {
	io::Logger::trace("StateManager: new state " + std::string(typeid(*state).name()));

	if (m_states.size()) {
		m_states.back()->freeze();
	}

	m_states.push_back(std::move(state));
}

void StateManager::popState() {
	io::Logger::trace("StateManager: popState request");

	m_popState = true;
}

utils::NoNullptr<State> StateManager::getCurrentState() const {
	return m_states.back().get();
}

bool StateManager::isToBeClosed() const noexcept {
	return m_isToExit;
}
