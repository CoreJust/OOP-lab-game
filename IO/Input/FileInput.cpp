// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "FileInput.h"

io::FileInput::FileInput(const float& mouseWheelDelta, const std::string& fileName) noexcept
    : VirtualInput(mouseWheelDelta), m_loader(fileName, /* is reading = */true) {
}

bool io::FileInput::update(float& deltaTime) {
    if (!m_loader.isOpen()) {
        return true; // Switching to keyboard input if the file is read completely
    }

    m_loader.read();
    deltaTime = m_loader.state().deltaTime;

    return false;
}

bool io::FileInput::isKeyPressed(const Key key) const {
    return m_loader.state().keysState[m_keyBindings.getKey(key)];
}

bool io::FileInput::isKeyReleased(const Key key) const {
    return !m_loader.state().keysState[m_keyBindings.getKey(key)];
}

bool io::FileInput::isMouseButtonPressed(const MouseButton btn) const {
    return m_loader.state().miceState[m_keyBindings.getMouseButton(btn)];
}

bool io::FileInput::isMouseButtonReleased(const MouseButton btn) const {
    return !m_loader.state().miceState[m_keyBindings.getMouseButton(btn)];
}

math::Vector2f io::FileInput::getMousePosition() const {
    return m_loader.state().mousePos;
}

float io::FileInput::getMouseWheelDelta() const {
    return m_loader.state().mouseWheelDelta;
}
