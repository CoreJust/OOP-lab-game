// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>

#include "IO/Logger.h"
#include "GlobalSettings.h"
#include "Graphics/GameGUI/TextAdapter.h"

#include "Game.h"

/*
*	Long-term TODO: main menu, world saves, inventory, audio, global settings loading from file
*	General TODO: Google test, minimap, custom input from file,
*				  3D graphics (openGL again? -yes, openGL)
*	Emergent TODO:
* 
*	Bugs:	collision breaks at top-left and down-right angles of non-passable blocks - fixed
*			runtime error after closing the main window directly and trying to close the console !
*			progress bars displayment as big white squares - fixed
*/

int main() {
	// Initializing
	io::Logger::Settings infoLoggerSettings = io::Logger::Settings {
		.printHeader = true, 
		.printDate = false, 
		.printTime = true, 
		.printSourceLocation = false 
	};

	io::Logger::Settings errorLoggerSettings = io::Logger::Settings {
		.printHeader = true,
		.printDate = true,
		.printTime = true,
		.printSourceLocation = true
	};

	io::Logger::initInfoLogger(std::cout, infoLoggerSettings);
	io::Logger::initErrorLogger(std::clog, errorLoggerSettings);
	io::Logger::logInfo("Initialized loggers");

	GlobalSettings::initSettings();
	io::Logger::logInfo("Loaded global settings");

	gamegui::TextAdapter::initTextAdapter();
	io::Logger::logInfo("Loaded text font");

	// Running the game
	Game game;
	game.run();

	// Releasing resources
	io::Logger::logInfo("Game cycle finished: beginning resources release");

	gamegui::TextAdapter::destroyTextAdapter();
	io::Logger::logInfo("Destroyed text font");

	GlobalSettings::destroySettings();
	io::Logger::logInfo("Destroyed global settings");

	io::Logger::destroyLoggers();

	system("pause");
	return 0;
}
