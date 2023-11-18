// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <string>
#include <fstream>

#include "IO/Input/InputState.h"

/*
*	InputFileLoader(.h/.cpp) contains a class that loads and parses or writes an input
*	file with the controls.
*/

namespace io {
	class InputFileLoader final {
	private:
		InputState m_state;
		std::fstream m_file;
		bool m_readingMode;

	public:
		InputFileLoader() = default;
		InputFileLoader(const std::string& fileName, bool isReading);
		~InputFileLoader();

		void read();
		void write();

		InputState& state() noexcept;
		const InputState& state() const noexcept;

		bool isOpen() const noexcept;
	};
}