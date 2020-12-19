
#define STB_IMAGE_IMPLEMENTATION // Required for stb_image.h (Only define once)

#include "game_engine.h"
#include "program_log.h"

int main (int argc, char **argv) {
	program_log("\n\nBegin Program");
	
	GameEngine engine;
	if(engine.initialize() == 0) {
		engine.game_loop();
		engine.deallocate();
	}

	return 0;
}

