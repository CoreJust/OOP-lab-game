// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "InputFileLoader.h"

#include <cassert>

#include "IO/Logger.h"

io::InputFileLoader::InputFileLoader(const std::string& fileName, bool isReading) 
	: m_readingMode(isReading) {
	if (fileName.empty()) {
		return;
	}

	m_file.open(fileName, std::ios::binary | (isReading ? std::ios::in : (std::ios::out | std::ios::trunc)));
	if (!m_file.is_open()) {
		io::Logger::logInfo("File not found: " + fileName + ", switching to manual input mode");
		return;
	}

	if (!m_file.good()) {
		io::Logger::logError("Failed to open the input file: " + fileName);
	}
}

io::InputFileLoader::~InputFileLoader() {
	if (m_file.is_open()) {
		m_file.close();
	}
}

io::InputState& io::InputFileLoader::state() noexcept {
	return m_state;
}

const io::InputState& io::InputFileLoader::state() const noexcept {
	return m_state;
}

bool io::InputFileLoader::isOpen() const noexcept {
	return m_file.is_open() && bool(m_file);
}

void io::InputFileLoader::read() {
	assert(m_readingMode && isOpen());

	if (!m_file) {
		state() = InputState();
		return;
	}

	std::string line;
	line.resize(InputState::STRING_REPRESENTATION_SIZE);

	m_file.read(&line[0], InputState::STRING_REPRESENTATION_SIZE);

	state().loadFromString(line);
}

void io::InputFileLoader::write() {
	assert(!m_readingMode && isOpen());

	std::string line = state().toString();
	m_file.write(&line[0], InputState::STRING_REPRESENTATION_SIZE);
	m_file.flush();
}
