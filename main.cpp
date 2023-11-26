// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>

#include "IO/Logger/Logger.h"
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
*	General TODO: Google test, minimap, more levels, cellular automatons generation, zooming the player in/out,
*				  review effects stacking, smth like TextureAtlas, but more generalized (probably just improve the Texture)
*	Emergent TODO:
* 
*	Bugs:	collision breaks at top-left and down-right angles of non-passable blocks - fixed
*			progress bars displayment as big white squares - fixed
*			having partially default bindings with user ones allows doubling of real commands - fixed
*			if player didn't move after teleportation, the camera was left in the previous position - fixed
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

	io::Logger::initLogger();
	GlobalSettings::initSettings();
	io::Logger::debug("main: initialized setting and loggers");

	gamegui::TextAdapter::initTextAdapter();

	utils::Random<>::initRandom();
	io::Logger::trace("main: initialized random");


	///  Running the game  ///

	{
		Game game;
		game.run();
	}


	///  Releasing resources  ///

	io::Logger::trace("main: game cycle finished; releasing resources...");

	utils::Random<>::destroyRandom();
	io::Logger::trace("main: destroyed random");

	gamegui::TextAdapter::destroyTextAdapter();
	GlobalSettings::destroySettings();
	io::Logger::debug("main: destroyed global settings");

	io::Logger::destroyLogger();

	system("pause");
	return 0;
}
