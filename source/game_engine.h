
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "generic/program_log.h"
#include "graphics/scene.h"

#include "../../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"

#include "graphics/graphics_wrapper_functions.h"

class GameEngine {
	private:
		Scene *scene;		// Holds current scene data

		glm::vec3 cameraPos;		// Camera location
		glm::vec3 cameraFront;	// Camera direction
		glm::vec3 cameraUp;		// Camera orientation

		bool firstMouse;		// Initialize previous and current position
		float yaw;			// Left-Right movement
		float pitch;			// Up-Down movement
		float lastX;			// Previous x-coordinate of cursor location
		float lastY;			// Previous y-coordinate of cursor location
		float fov;			// Field Of View

		float deltaTime;	// Time between current frame and last frame
		float lastFrame;	// Time last frame was finished
		unsigned int fps;// Frames per second of the program
		
	public:
		GameEngine();		// Default constructor
		~GameEngine();		// Default destructor
		int initialize();	// Initialize window with OpenGL
		void game_loop();	// The main game loop
};
#endif
