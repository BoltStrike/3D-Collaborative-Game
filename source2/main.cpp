
#define STB_IMAGE_IMPLEMENTATION // Required for stb_image.h (Only define once)

#include "game_engine.h"
#include "generic/program_log.h"

/******************************************************************************
 * This is the main function. This starts the game engine, enters the game loop
 * and terminates the game engine after it is finished. 
******************************************************************************/
int main (int argc, char **argv) {
	program_log("\n\nBegin Program\n", true);	// Create new log file
	
	GameEngine engine;
	if(engine.initialize() == 0) 
		engine.game_loop();

	program_log("End Program\n");
	return 0;
}

