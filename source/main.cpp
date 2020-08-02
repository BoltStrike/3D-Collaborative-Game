/******************************************************************************
** File: main.cpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 4 July 2020
** Description: Holds the main function of the whole program
******************************************************************************/



#include "gameEngine.h"
#include <iostream>

using namespace std;

/******************************************************************************
** Function: main
** Description: This is the start of the entire program. 
** Parameters: int argc holds the number of arguments, char **argv holds the 
** string of characters that hold the arguments
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
int main (int argc, char **argv) {
	GameEngine engine;
	bool success = engine.initialize(argc, argv);
	if (success) {
		engine.run();
	}
	else {
		cout << "Failed to initiallize game engine" << endl;
	}

	engine.shutdown();

	return 0;
}
