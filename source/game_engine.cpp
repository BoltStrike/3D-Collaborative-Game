
#include "game_engine.h"

// Screen dimensions
unsigned int GameEngine::scr_width{800};
unsigned int GameEngine::scr_height{600};

// camera
glm::vec3 GameEngine::cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)};
glm::vec3 GameEngine::cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};
glm::vec3 GameEngine::cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)};

// Mouse movement
bool GameEngine::firstMouse{true};
// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a 
// direction vector pointing to the right so we initially rotate a bit 
// to the left.
float GameEngine::yaw{-90.0f};	
float GameEngine::pitch{0.0f};
float GameEngine::lastX{ ( (float)GameEngine::scr_width ) / 2.0f};
float GameEngine::lastY{ ( (float)GameEngine::scr_height ) / 2.0f};
float GameEngine::fov{45.0f};

// Timing
float GameEngine::deltaTime{0.0f};
float GameEngine::lastFrame{0.0f};

/******************************************************************************
 * This is the default constructor
 *****************************************************************************/
GameEngine::GameEngine () {

}

/******************************************************************************
 * This function initializes a GLFW window with OpenGL.
 *****************************************************************************/
int GameEngine::initialize () {
	// glfw: initialize and configure OpenGL v3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__	// Only for Mac OS
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// glfw window creation
	window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)	{
		program_log("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		program_log("Failed to initialize GLAD");
		return -1;
	}
	
	// configure global opengl state
	glEnable(GL_DEPTH_TEST);	

	scene.load("assets/amerature_test/scene1.scene");
	return 0;
}

/******************************************************************************
 * This function deallocates all memory with the game and shuts it down.
 *****************************************************************************/
void GameEngine::deallocate () {
	glfwTerminate();	// clear all allocated GLFW resources
}

/******************************************************************************
 * This function is the main game loop. 
******************************************************************************/
void GameEngine::game_loop () {
	while (!glfwWindowShouldClose(window)) {
		// Time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);	// Input

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.draw(fov, scr_width, scr_height, cameraPos,  cameraFront, cameraUp);

		glfwSwapBuffers(window);	// Swap buffers
		glfwPollEvents();			// Poll IO events
	}
}

/******************************************************************************
 * This function is the callback that queries GLFW for the keys being pressed
 * and reacts accordingly.
 *****************************************************************************/
void GameEngine::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	// ESC 
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		// W
		GameEngine::cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)		// S
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)		// A
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)		// D
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

/******************************************************************************
 * This function is the callback that adjusts the viewport whenever the 
 * window size changes.
 * Params:
 *		window	- GLFWwindow being drawn to
 *		width	- New width of the window
 *		height	- New height of the window
******************************************************************************/
void GameEngine::framebuffer_size_callback(GLFWwindow* window, 
										   int width, 
										   int height) {
	// ensure viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

/******************************************************************************
 * This function is the callback that handles mouse movement. When the mouse
 * moves, the view is adjusted.
 * Params:
 *		window 	- GLFWwindow being drawn to
 *		xpos	- X-coordinate of the location of the cursor on the screen
 *		ypos	- Y-coordinate of the location of the cursor on the screen
******************************************************************************/
void GameEngine::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {	// Only for the first time, set the previous location
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;	// x-coordinates go from left to right
	float yoffset = lastY - ypos; 	// y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

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
}

/******************************************************************************
 * This function is the callback that activates whenever the mouse scroll
 * wheel scrolls. 
 * Params:
 *		window	- GLFWwindow being drawn to
 *		xoffset	- Amount the scroll wheel scrolled along the x-axis (unusual)
 *		yoffset	- Amount the scroll wheel scrolled along the y-axis
 *****************************************************************************/
void GameEngine::scroll_callback(GLFWwindow* window, 
								 double xoffset, 
								 double yoffset) {
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
