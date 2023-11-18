// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <SFML/Window/Mouse.hpp>

#include "VirtualInput.h"
#include "IO/File/InputFileLoader.h"

/*
*	FileInput(.h/.cpp) contains a class that inherits VirtualInput and represents
*	the input from a file.
*
*	It redirects the input scanning from a file into the virtual input.
*/

namespace io {
	class FileInput final : public VirtualInput {
	private:
		InputFileLoader m_loader;

	public:
		FileInput(const float& mouseWheelDelta, const std::string& fileName) noexcept;

		bool update(float& deltaTime) override;

		bool isKeyPressed(const Key key) const override;
		bool isKeyReleased(const Key key) const override;

		bool isMouseButtonPressed(const MouseButton btn) const override;
		bool isMouseButtonReleased(const MouseButton btn) const override;

		math::Vector2f getMousePosition() const override;
		float getMouseWheelDelta() const override;
	};
}