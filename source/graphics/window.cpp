
#include "window.h"

/******************************************************************************
 * Initiate all the static variables in the class. These need to be initiated
 * before the creation of the object to ensure they can be accessed from
 * outside functions.
******************************************************************************/
// Screen dimensions
unsigned int Window::scr_width{1600};
unsigned int Window::scr_height{900};

// camera
glm::vec3 Window::cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)};
glm::vec3 Window::cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};
glm::vec3 Window::cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)};

// Mouse movement
bool Window::firstMouse{true};
// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a 
// direction vector pointing to the right so we initially rotate a bit 
// to the left.
float Window::yaw{-90.0f};	
float Window::pitch{0.0f};
float Window::lastX{ ( (float)Window::scr_width ) / 2.0f};
float Window::lastY{ ( (float)Window::scr_height ) / 2.0f};
float Window::fov{45.0f};

// Timing
float Window::deltaTime{0.0f};
float Window::lastFrame{0.0f};
unsigned int Window::fps{30};

/******************************************************************************
 * This is the default constructor
******************************************************************************/
Window::Window () {

}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
Window::~Window () {
	glfwTerminate();	// clear all allocated GLFW resources
}

/******************************************************************************
 * This function creates a GLFW window with OpenGL context. By doing this,
 * OpenGL is loaded using GLAD. Returns 0 on success. Anything else is failure.
 * Params:
 *		width	- The width of the window in pixels
 *		height	- The height of the window in pixels
 *		name	- The title of the window
******************************************************************************/
int Window::create_window (unsigned int width, 
							unsigned int height, 
							const char* name) {

	program_log("Creating window...\n");
	
	Window::scr_width = width;
	Window::scr_height = height;
	
	// glfw: initialize and configure OpenGL v3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__	// Only for Mac OS
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// glfw window creation
	window = glfwCreateWindow(scr_width, scr_height, name, NULL, NULL);
	if (window == NULL)	{
		program_log("ERROR::Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set the callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		program_log("ERROR::Failed to initialize GLAD\n");
		return -1;
	}
	
	// configure global opengl state
	glEnable(GL_DEPTH_TEST);	// Correct face layering
	glEnable(GL_CULL_FACE);		// Backface culling
	glCullFace(GL_BACK);		// Cull the backs of faces
	glFrontFace(GL_CCW);  		// Set counter-clock-wise as the front face 
	// Blending functionality (transparency)
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	program_log("Created window\n");
	return 0;	
}

/******************************************************************************
 * This function enables v-sync on the window.
******************************************************************************/
void Window::set_vsync (bool state) {
	if(state) { 
		glfwSwapInterval(1);	// Enable v-sync if state is true
		program_log("Set V-Sync: On\n");
	}
	else {
		glfwSwapInterval(0);	// Disable v-sync if state is false
		program_log("Set V-Sync: Off\n");
	}
}

/******************************************************************************
 * This function suspends the program for the specifed amount of time in
 * microseconds.
******************************************************************************/
void Window::sleep (double seconds) {
	sleep(seconds);
}

/******************************************************************************
 * This function sets the timing variables, gathers the relevant input, and
 * clears the viewport in preparation for rendering the next frame.
******************************************************************************/
void Window::prepare () {
	// Time logic
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	processInput(window);	// Input
	
	// Clear viewport
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/******************************************************************************
 * This function gets the input and resets the viewport for the next frame.
 * If the program is running to fast, the program will be suspended for brief
 * intervals to regulate the speed. 
******************************************************************************/
void Window::input () {
	glfwSwapBuffers(window);	// Swap buffers
	glfwPollEvents();			// Poll IO events
	//float currentFrame = glfwGetTime();
	//if(currentFrame - lastFrame < 1.0f/fps) 
	//	sleep(1.0f/fps - (currentFrame - lastFrame));
}

/******************************************************************************
 * This function signifies when the render loop should stop. It accomplishes
 * this by checking whether the GLFW window has been told to close.
******************************************************************************/
bool Window::should_close () {
	return glfwWindowShouldClose(window);
}

/******************************************************************************
 * This function is the callback that queries GLFW for the keys being pressed
 * and reacts accordingly.
 *****************************************************************************/
void Window::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	// ESC 
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)		// W
		cameraPos += cameraSpeed * cameraFront;
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
void Window::framebuffer_size_callback(GLFWwindow* window, 
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
void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
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
void Window::scroll_callback(GLFWwindow* window, 
								 double xoffset, 
								 double yoffset) {
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)

		fov = 45.0f;
}
