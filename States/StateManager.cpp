// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "StateManager.h"

#include "IO/Input/KeyboardMouseInput.h"
#include "IO/Logger.h"
#include "GlobalSettings.h"
#include "GameState.h"

StateManager::StateManager(const float& mouseWheelDelta)
	: m_virtualInput(std::make_unique<io::KeyboardMouseInput>(mouseWheelDelta)) {
	io::Logger::logInfo("Initialized input");

	addState(std::make_unique<GameState>(*this));
}

void StateManager::update(sf::RenderWindow& window, float deltaTime) {
	if (GlobalSettings::get().isToLogDeltaTime()) {
		io::Logger::logInfo("StateManager update with deltaTime: " + std::to_string(deltaTime));
	}

	getCurrentState()->update(deltaTime, m_virtualInput.get());
	getCurrentState()->render(window);

	if (m_popState) {
		m_popState = false;
		m_states.pop_back();

		m_isToExit = m_states.size() == 0;

		io::Logger::logInfo("StateManager: state popped, states left " + std::to_string(m_states.size()));
	}
}

void StateManager::addState(std::unique_ptr<State> state) {
	io::Logger::logInfo("StateManager: new state " + std::string(typeid(*state).name()));

	m_states.push_back(std::move(state));
}

void StateManager::popState() {
	io::Logger::logInfo("StateManager: popState request");

	m_popState = true;
}

utils::NoNullptr<State> StateManager::getCurrentState() const {
	return m_states.back().get();
}

bool StateManager::isToBeClosed() const noexcept {
	return m_isToExit;
}
