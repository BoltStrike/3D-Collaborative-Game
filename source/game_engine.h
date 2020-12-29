
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "generic/program_log.h"
#include "graphics/window.h"
#include "graphics/scene.h"

#include "generic/program_log.h"

class GameEngine {
	private:
		Window *window;		// The GLFW window with OpenGL context
		Scene *scene;		// Holds current scene data
		
	public:
		GameEngine();		// Default constructor
		~GameEngine();		// Default destructor
		int initialize();	// Initialize window with OpenGL
		void game_loop();	// The main game loop
};
#endif
