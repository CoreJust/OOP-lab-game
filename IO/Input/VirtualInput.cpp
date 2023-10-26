#include "VirtualInput.h"

#include <cassert>

#include "KeyboardMouseInput.h"
#include "IO/File/KeyBindingsLoader.h"

void io::VirtualInput::initBindings() {
	KeyBindingsLoader loader(m_keyBindings);
	loader.load();
}

std::unique_ptr<io::VirtualInput> io::VirtualInput::makeVirtualInput(InputMode mode, const float& mouseWheelDelta) {
	switch (mode) {
		case io::KEYBOARD_AND_MOUSE_INPUT: return std::make_unique<io::KeyboardMouseInput>(mouseWheelDelta);
		case io::FILE_INPUT: break;
	default: break;
	}

	assert(false && "unreachable");
}
