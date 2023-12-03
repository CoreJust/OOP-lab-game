// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "VirtualInput.h"

#include <cassert>

#include "GlobalSettings.h"
#include "KeyboardMouseInput.h"
#include "FileInput.h"
#include "IO/File/KeyBindingsLoader.h"

io::VirtualInput::VirtualInput(const float& mouseWheelDelta) : m_mouseWheelDelta(mouseWheelDelta) { }

void io::VirtualInput::initBindings() {
	KeyBindingsLoader loader(m_keyBindings);
	loader.load();
}

const float& io::VirtualInput::getMouseWheelDeltaRef() const noexcept {
	return m_mouseWheelDelta;
}

std::unique_ptr<io::VirtualInput> io::VirtualInput::makeVirtualInput(const InputMode mode, const float& mouseWheelDelta) {
	std::unique_ptr<io::VirtualInput> result;

	switch (mode) {
		case InputMode::KEYBOARD_AND_MOUSE_INPUT: result = std::make_unique<io::KeyboardMouseInput>(mouseWheelDelta); break;
		case InputMode::FILE_INPUT: result = std::make_unique<io::FileInput>(mouseWheelDelta, GlobalSettings::get().getInputFile()); break;
	default: assert(false && "unreachable"); break;
	}

	result->initBindings();
	return result;
}
