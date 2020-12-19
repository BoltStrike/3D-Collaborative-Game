
#ifndef WINDOW_H
#define WINDOW_H

#include "../../glad/glad.h"
#include "../../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include "../generic/program_log.h"

class Window {
	private:
		GLFWwindow *window;	// Window to be drawing to

	public:
		static unsigned int scr_width;	// Screen width
		static unsigned int scr_height;	// Screen height

		static glm::vec3 cameraPos;		// Camera location
		static glm::vec3 cameraFront;	// Camera direction
		static glm::vec3 cameraUp;		// Camera orientation

		static bool firstMouse;		// Initialize previous and current position
		static float yaw;			// Left-Right movement
		static float pitch;			// Up-Down movement
		static float lastX;			// Previous x-coordinate of cursor location
		static float lastY;			// Previous y-coordinate of cursor location
		static float fov;			// Field Of View

		static float deltaTime;	// Time between current frame and last frame
		static float lastFrame;	// Time last frame was finished
	
		Window();	// Default constructor
		~Window();	// Default destructor
		
		// Creates GLFW window with OpenGL context. Initializes OpenGL.
		int create_window(unsigned int, unsigned int, const char*);
		void prepare();			// Prepares the window for the next frame
		bool should_close();	// Signifies if the render loop should stop

		// Callback functions
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void processInput(GLFWwindow* window);
};
#endif
