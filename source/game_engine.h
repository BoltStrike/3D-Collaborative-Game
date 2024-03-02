
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

#include "physics/physicsManager.h"
#include "physics/allColliders.h"
#include "physics/internalPhysics.h"
#include "generic/file_tosstream.h"

#include <time.h>

class GameEngine {
	private:
		Scene *scene;		    // Holds current scene data

		glm::vec3 cameraPos;	// Camera location
		glm::vec3 cameraFront;	// Camera direction
		glm::vec3 cameraUp;		// Camera orientation

		float yaw;			    // Left-Right movement
		float pitch;			// Up-Down movement
		float lastX;			// Previous x-coordinate of cursor location
		float lastY;			// Previous y-coordinate of cursor location
		float fov;			    // Field Of View

		float deltaTime;	    // Time between current frame and last frame
		clock_t lastFrame;	    // Time last frame was finished
		unsigned int fps;       // Frames per second of the program
		
		PhysicsManager physicsManager;
		ResolvableCollider* playerCollider;
		//MeshCollider* mesh;
		MeshCollider* mc_cave;
		MeshCollider* mc_main_grass;
		MeshCollider* mc_rock;
		MeshCollider* mc_tree;
		MeshCollider* mc_trim_grass;
		MeshCollider* mc_underside;
		MeshCollider* mc_water;
		
	public:
		GameEngine();		// Default constructor
		~GameEngine();		// Default destructor
		int initialize();	// Initialize window with OpenGL
		void game_loop();	// The main game loop
};
#endif
