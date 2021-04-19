
#include "input.h"

namespace in { 	// All of these public functions are under the "in" scope

double cursor_x;
double cursor_y;
double scroll_x;
double scroll_y;

// Unordered maps containing paired inputs
std::unordered_map<int, bool> glfwinputs;		// Map GLFW ID to bool

/******************************************************************************
 * This function returns true if the requested mouse button or keyboard key is
 * currently pressed.
******************************************************************************/
bool btn (int button) {
	return glfwinputs[button];
}

/******************************************************************************
 * This function returns the location of the cursor by altering the variables
 * passed by reference.
******************************************************************************/
void get_mouse (double &x, double &y) {
	x = cursor_x;
	y = cursor_y;
}

/******************************************************************************
 * This function returns the scroll wheel position by altering the variables
 * passed by reference.
******************************************************************************/
void get_scroll (double &x, double &y) {
	x = scroll_x;
	y = scroll_y;
}

/******************************************************************************
 * This function polls for the current state of I/O.
******************************************************************************/
void poll_events () {
	glfwPollEvents();			// Poll IO events
}

/******************************************************************************
 * This function returns the time since the program began as a float 
 * representing seconds.
******************************************************************************/
float get_time () {
	return glfwGetTime();
}

/******************************************************************************
 * This function is the callback that adjusts the keyboard state whenever a key
 * is pressed.
 * Params:
 *		window	- GLFWwindow being drawn to
 *		key		- Integer ID of the key being pressed (managed by GLFW)
 *		scancode- Platform-specific ID of the key being pressed (managed by OS)
 *		action	- What the key is doing (GLFW_PRESS, GLFW_REPEAT, GLFW_RELEASE, 
 *				  or GLFW_KEY_UNKNOWN)
 * 		mods	- Modifier bits representing Caps-lock or num-lock		  
******************************************************************************/
void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
		glfwinputs[key] = true;
	else if (action == GLFW_REPEAT)
		glfwinputs[key] = true;
	else if (action == GLFW_RELEASE)
		glfwinputs[key] = false;
	else
		glfwinputs[key] = false;
}

/******************************************************************************
 * This function changes the state of the mouse buttons whenever a mouse
 * button is pressed.
 * Params:
 *		window	- GLFWwindow being drawn to
 *		button	- Integer ID for the button being pressed
 *		action	- The process being done on the button
 *		mods	- Modification bits for sticky buttons
******************************************************************************/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS)
		glfwinputs[button] = true;
	else if (action == GLFW_RELEASE)
		glfwinputs[button] = false;
	else
		glfwinputs[button] = false;
}

/******************************************************************************
 * This function is the callback that handles mouse movement. When the mouse
 * moves, the view is adjusted.
 * Params:
 *		window 	- GLFWwindow being drawn to
 *		xpos	- X-coordinate of the location of the cursor on the screen
 *		ypos	- Y-coordinate of the location of the cursor on the screen
******************************************************************************/
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	cursor_x = xpos;
	cursor_y = ypos;
}

/******************************************************************************
 * This function is the callback that activates whenever the mouse scroll
 * wheel scrolls. 
 * Params:
 *		window	- GLFWwindow being drawn to
 *		xoffset	- Amount the scroll wheel scrolled along the x-axis (unusual)
 *		yoffset	- Amount the scroll wheel scrolled along the y-axis
 *****************************************************************************/
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	scroll_x = xoffset;
	scroll_y = yoffset;
}

}//namespace in
