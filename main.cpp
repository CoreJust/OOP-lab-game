// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>

#include "IO/Logger.h"
#include "Utils/Random.h"
#include "GlobalSettings.h"
#include "Graphics/GameGUI/TextAdapter.h"

#include "Game.h"

/*
*	main.cpp contains a single function int main() - the only non-method function in this work.
* 
*	In this function all global states (such as I/O and settings) are being initialized and later
*	released. In between these two stages the game is being run.
*/

/*
*	Long-term TODO: world saves, inventory, audio, enemies, player stats interface, frustum
*	General TODO: Google test, minimap, more levels, cellular automatons generation, zooming the player in/out
*	Emergent TODO:
* 
*	Bugs:	collision breaks at top-left and down-right angles of non-passable blocks - fixed
*			progress bars displayment as big white squares - fixed
*			having partially default bindings with user ones allows doubling of real commands - fixed
* 
*			accidental runtime error after closing the main window directly and trying to close the console ?
*			if the console is selected and we tap "play", then move the mouse out of the window
*				and remove selection, then the mouse gets stuck there unless we press escape and
*				move the mouse back to the window !
*			in the recentmost version the file input acts strange - it reproduces actions not exactly !
*			in the file input mode user cannot conveniently close the game !
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

	utils::Random<>::initRandom();
	io::Logger::logInfo("Initialized random");


	///  Running the game  ///

	{
		Game game;
		game.run();
	}


	///  Releasing resources  ///

	io::Logger::logInfo("Game cycle finished; releasing resources...");

	utils::Random<>::destroyRandom();
	io::Logger::logInfo("Destroyed random");

	gamegui::TextAdapter::destroyTextAdapter();
	io::Logger::logInfo("Destroyed text font");

	GlobalSettings::destroySettings();
	io::Logger::logInfo("Destroyed global settings");

	io::Logger::destroyLoggers();

	system("pause");
	return 0;
}
