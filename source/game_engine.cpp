
#include "game_engine.h"

/******************************************************************************
 * This is the default constructor
******************************************************************************/
GameEngine::GameEngine () {

}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
GameEngine::~GameEngine () {

}

/******************************************************************************
 * This function initializes a GLFW window with OpenGL.
 *****************************************************************************/
int GameEngine::initialize () {
	if(window.create_window(800, 600, "Reworked Game Engine") != 0)
		return -1;

	scene.load("assets/amerature_test/scene1.scene");
	return 0;
}

/******************************************************************************
 * This function is the main game loop. 
******************************************************************************/
void GameEngine::game_loop () {
	while (!window.should_close()) {
		window.prepare();
		scene.draw();
	}
}

