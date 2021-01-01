
#include "game_engine.h"

/******************************************************************************
 * This is the default constructor
******************************************************************************/
GameEngine::GameEngine () {
	window = new Window;
	scene = new Scene;
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
GameEngine::~GameEngine () {
	program_log("Deleting engine...\n");

	delete scene;
	delete window;
	program_log("Deleted engine\n");
}

/******************************************************************************
 * This function initializes a GLFW window with OpenGL.
 *****************************************************************************/
int GameEngine::initialize () {
	program_log("Initializing engine...\n");

	if(window->create_window(1600, 900, "Reworked Game Engine") != 0)
		return -1;

	window->set_vsync(true);

	const char *default_scene = "assets/scenes/floating_island.scene";
	scene->load(default_scene);	// Load default scene

	program_log("Initalized engine\n\n");
	return 0;
}

/******************************************************************************
 * This function is the main game loop. 
******************************************************************************/
void GameEngine::game_loop () {
	program_log("Begin Game Loop\n");
	while (!window->should_close()) {
		window->prepare();	// Clear viewport, compute times, and gather inputs
		scene->draw();		// Draw next frame from this scene
		window->input();
	}
	program_log("Game Loop Stopped\n");
}

