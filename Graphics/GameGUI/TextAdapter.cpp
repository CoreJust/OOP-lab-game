// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "TextAdapter.h"
#include <cassert>

#include "IO/File/FileLoader.h"
#include "IO/Logger/Logger.h"
#include "GlobalSettings.h"

gamegui::TextAdapter::TextAdapter(std::string_view fileName) {
	io::FileLoader loader(GlobalSettings::get().getFontsLocation(), ".ttf");
	if (!m_font.loadFromFile(loader.getFullPath(fileName))) {
		io::Logger::error("TextAdapter: failed to load font " + std::string(fileName));
	} else {
		io::Logger::debug("TextAdapter: loaded font successfully");
	}
}

void gamegui::TextAdapter::initTextAdapter() {
	assert(s_instance == nullptr);

	s_instance = new TextAdapter(GlobalSettings::get().getTextFont());
	io::Logger::debug("TextAdapter: initialized");
}

void gamegui::TextAdapter::destroyTextAdapter() {
	assert(s_instance != nullptr);

	delete s_instance;
	s_instance = nullptr;
	io::Logger::debug("TextAdapter: destroyed");
}

sf::Font& gamegui::TextAdapter::getFont() {
	assert(s_instance != nullptr);

	return s_instance->m_font;
}
