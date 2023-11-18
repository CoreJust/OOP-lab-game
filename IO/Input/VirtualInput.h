// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cstdint>

#include "Math/Vector.h"
#include "InputMode.h"
#include "KeyBindings.h"

/*
*	VirtualInput(.h/.cpp) contains a base class for all the input schemes.
*
*	It provides the interface for getting the input from the user
*	and manages the bindings.
*/

namespace io {
	// Basic class for all the input classes
	// An interface that allows to get user input as if from keyboard and mouse
	// Might have implementations (via inheritance) that would in fact use network or file for input
	class VirtualInput {
	protected:
		KeyBindings m_keyBindings;
		const float& m_mouseWheelDelta;

	public:
		VirtualInput(const float& mouseWheelDelta);
		virtual ~VirtualInput() noexcept = default;

		// delta is changed in FileInput and is (possibly) read in KeyboardMouseInput
		// If returns true, then the input mode is changed to keyboard and mouse no matter the current
		virtual bool update(float& deltaTime) = 0; 

		virtual bool isKeyPressed(const Key key) const = 0;
		virtual bool isKeyReleased(const Key key) const = 0;

		virtual bool isMouseButtonPressed(const MouseButton btn) const = 0;
		virtual bool isMouseButtonReleased(const MouseButton btn) const = 0;

		virtual math::Vector2f getMousePosition() const = 0;
		virtual float getMouseWheelDelta() const = 0;

		void initBindings();

		const float& getMouseWheelDeltaRef() const noexcept;

		static std::unique_ptr<VirtualInput> makeVirtualInput(const InputMode mode, const float& mouseWheelDelta);
	};
}