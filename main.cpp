// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>

#include "IO/Logger.h"
#include "GlobalSettings.h"
#include "Graphics/GameGUI/TextAdapter.h"

#include "Game.h"

#include "IO/Json/JsonParser.h"

/*
*	main.cpp contains a single function int main() - the only non-OOP function in this work.
* 
*	In this function all global states (such as I/O and settings) are being initialized and later
*	released. In between these two stages the game is being run.
*/

/*
*	Long-term TODO: world saves, inventory, audio
*	General TODO: Google test, minimap, main menu, more levels, cellular automatons and random generation,
*				  3D graphics (openGL again? -yes, openGL)
*	Emergent TODO: custom input from file
* 
*	Bugs:	collision breaks at top-left and down-right angles of non-passable blocks - fixed
*			runtime error after closing the main window directly and trying to close the console !
*			progress bars displayment as big white squares - fixed
*/

int main() {
	///  Initializing  ///

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


	///  Running the game  ///

	Game game;
	game.run();


	///  Releasing resources  ///

	io::Logger::logInfo("Game cycle finished: beginning resources release");

	gamegui::TextAdapter::destroyTextAdapter();
	io::Logger::logInfo("Destroyed text font");

	GlobalSettings::destroySettings();
	io::Logger::logInfo("Destroyed global settings");

	io::Logger::destroyLoggers();

	system("pause");
	return 0;
}
