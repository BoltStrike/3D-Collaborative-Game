/*****************************************************************************
** File: window_framework.cpp
** Project: 3D Collaborative Game
** Author: Andrew Johnson
** Date Created: 1 August 2020
** Description: Holds all the functions for the WindowFramework class
*****************************************************************************/

#include "window_framework.h"


WindowFramework::WindowFramework () {
	window_width = 1280;
	window_height = 720;
	key_sensitivity = 1;
	mouse_sensitivity = 0.1;
	keyboard_state = new bool[256];
	for (int i=0; i < 256; i++) {
		keyboard_state[i] = false;
	}
	mouse_x = 0;
	mouse_y = 0;
	yaw = 0.0;
	pitch = 0.0;
}


WindowFramework::~WindowFramework () {
	
}


int WindowFramework::initialize () {
	// Basic initialization
	if (!glfwInit()) {
		std::cout << "Failed to initalize GLFW" << std::endl;
		return -1;
	}
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // glfw window creation
    window = glfwCreateWindow(window_width, window_height, "3D Collaborative Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    framebuffer_size_callback(window, window_width, window_height);

	framebuffer_size_callback(window, window_width, window_height);
	graphics.initialize();
    
	return 0;
}


void WindowFramework::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void WindowFramework::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective_gl(45.0, (double)width / (double)height, 1.0, 200.0);
}

void WindowFramework::perspective_gl( double fovY, double aspect, double zNear, double zFar )
{
    const double pi = 3.1415926535897932384626433832795;
    double fW, fH;

    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}


int WindowFramework::render () {
	graphics.draw();
	glfwSwapBuffers(window);
	return 0;
}


void WindowFramework::terminate () {
	graphics.terminate();
	glfwTerminate();
}


void WindowFramework::mouse_movement (int x, int y) {
	double w = window_width;
	double h = window_height;
	adjust_view(x, y, w, h, mouse_sensitivity);
	if (x <= w/4 || x >= w*3/4) {
		//glutWarpPointer(w/2, y);
	}
	if (y <= h/4 || y >= h*3/4) {
		//glutWarpPointer(x, h/2);
	}
}

void WindowFramework::adjust_view (int x, int y, int width, int height, double sens) {
	if (x <= width/4 || x >= width*3/4) {
		x = width/2;
		mouse_x = width/2;
	}
	if (y <= height/4 || y >= height*3/4) {
		y = height/2;
		mouse_y = height/2;
	}
	yaw += sens*(x-mouse_x);
	pitch += sens*(y-mouse_y);
	mouse_x = x;
	mouse_y = y;
}


void WindowFramework::key_callback() {
	// Upon press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    	keyboard_state['w'] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    	keyboard_state['a'] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		keyboard_state['s'] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		keyboard_state['d'] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		keyboard_state['q'] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		keyboard_state['e'] = true;
	}

	// Upon release
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
    	keyboard_state['w'] = false;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
    	keyboard_state['a'] = false;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
		keyboard_state['s'] = false;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
		keyboard_state['d'] = false;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
		keyboard_state['q'] = false;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
		keyboard_state['e'] = false;
	}
	
	graphics.handle_input(keyboard_state);
}
