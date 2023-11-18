// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TextAdapter.h"
#include <cassert>

#include "IO/File/FileLoader.h"
#include "IO/Logger.h"
#include "GlobalSettings.h"

gamegui::TextAdapter::TextAdapter(std::string_view fileName) {
	io::FileLoader loader(GlobalSettings::get().getFontsLocation(), ".ttf");
	if (!m_font.loadFromFile(loader.getFullPath(fileName))) {
		io::Logger::logError("Failed to load font: " + std::string(fileName));
	}
}

void gamegui::TextAdapter::initTextAdapter() {
	assert(s_instance == nullptr);

	s_instance = new TextAdapter(GlobalSettings::get().getTextFont());
}

void gamegui::TextAdapter::destroyTextAdapter() {
	assert(s_instance != nullptr);

	delete s_instance;
	s_instance = nullptr;
}

sf::Font& gamegui::TextAdapter::getFont() {
	assert(s_instance != nullptr);

	return s_instance->m_font;
}
