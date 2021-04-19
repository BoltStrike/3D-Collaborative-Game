
#include "game_engine.h"


/******************************************************************************
 * This is the default constructor
******************************************************************************/
GameEngine::GameEngine () {
	//window = new Window;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	fov = 45.0f;
	firstMouse = true;
	yaw = -90.0f;
	pitch = 0.0f;
	
	scene = new Scene;
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
GameEngine::~GameEngine () {
	program_log("Deleting engine...\n");

	delete scene;
	//delete window;
	program_log("Deleted engine\n");
}

/******************************************************************************
 * This function initializes a GLFW window with OpenGL.
 *****************************************************************************/
int GameEngine::initialize () {
	program_log("Initializing engine...\n");

	//if(window->create_window(1600, 900, "Reworked Game Engine") != 0)
	//	return -1;

	gwf::initialize_glfw();
	std::string name = "Test Window";
	gwf::create_window(1600, 900, name);
	gwf::set_window(name);
	gwf::set_cursor(false);

	if (!gwf::load_opengl())	return -1;
	gwf::set_depth_test(true);			// Sets depth testing to given Boolean
	gwf::set_backface_culling(true);	// Sets backface culling to given Boolean
	gwf::set_blending(true);			// Sets blending functionality to Boolean
	gwf::set_vsync(true);

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
	while (!gwf::should_close()) {
		// Time logic
		float currentFrame = in::get_time();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		gwf::clear_viewport(0.2f, 0.3f, 0.3f);

//*********************************/
	
		//glfwGetCursorPos(glfwGetCurrentContext(), &in::cursor_x, &in::cursor_y);

		if (firstMouse) {	// Only for the first time, set the previous location
			lastX = in::cursor_x;
			lastY = in::cursor_y;
			firstMouse = false;
		}

		//std::string message = "X: ";
		//program_log(message.append(std::to_string(in::cursor_x)).append(" Y: ").append(std::to_string(in::cursor_y)).append("\n"));

		float xoffset = in::cursor_x - lastX;	// x-coordinates go from left to right
		float yoffset = lastY - in::cursor_y; 	// y-coordinates go from bottom to top
		lastX = in::cursor_x;
		lastY = in::cursor_y;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
//*********************************/
	fov -= (float)in::scroll_y;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)

		fov = 45.0f;
//*********************************/
	if (in::btn(in::ESCAPE))	// ESC 
		gwf::close();

	float cameraSpeed = 2.5 * deltaTime * 5.0;
	if (in::btn(in::W))		// W
		cameraPos += cameraSpeed * cameraFront;
	if (in::btn(in::S))		// S
		cameraPos -= cameraSpeed * cameraFront;
	if (in::btn(in::A))		// A
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (in::btn(in::D))		// D
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;



		int width, height;
		gwf::get_dimensions(width, height);
		scene->draw(fov, width, height, cameraPos, cameraFront, cameraUp);		// Draw next frame from this scene
		gwf::swap_buffers();
		//std::string message = "Before: X:";
		//program_log(message.append(std::to_string(in::cursor_x)).append(" Y:").append(std::to_string(in::cursor_y)).append("\n"));
		in::poll_events();
		//message = "After: X:";
		//program_log(message.append(std::to_string(in::cursor_x)).append(" Y:").append(std::to_string(in::cursor_y)).append("\n"));
	}
	gwf::terminate_glfw();	// Deallocate GLFW resources
	program_log("Game Loop Stopped\n");
}

