/*****************************************************************************
** File: window_framework.h
** Project: 3D Collaborative Game
** Author: Andrew Johnson
** Date Created: 1 August 2020
** Description: Defines the WindowFramework class
*****************************************************************************/


#ifndef WINDOW_FRAMEWORK_H
#define WINDOW_FRAMEWORK_H

#include <cmath>
#include <iostream>
#include <stdio.h>

// the GLFW and OpenGL libraries have to be linked correctly
#ifndef _GLAD_
#define _GLAD_
#include "../glad/glad.h"
#endif
#include "../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"


class WindowFramework {
	private:
		double key_sensitivity;
		double mouse_sensitivity;
		int mouse_x;
		int mouse_y;
		bool* keyboard_state;
		
	public:
		GLFWwindow *window;
		double yaw;
		double pitch;
		int window_width = 1280;
		int window_height = 720;
		WindowFramework();
		~WindowFramework();
		int initialize();
		static void error_callback(int, const char*);
		static void framebuffer_size_callback(GLFWwindow*, int, int);
		static void perspective_gl(double, double, double, double);
		int render();
		void terminate();
		void mouse_movement(int, int);
		void adjust_view (int, int, int, int, double);
		void key_callback();
};


#endif
