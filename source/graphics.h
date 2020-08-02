/******************************************************************************
** File: graphics.hpp
** Project: 3D Collaborative Game
** Date Created: 12 July 2020
** Description: Creates an object to handle all OpenGL and GLUT window 
** operations and commands
******************************************************************************/


#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

// the GLFW and OpenGL libraries have to be linked correctly
#ifndef _GLAD_
#define _GLAD_
#include "../glad/glad.h"
#endif
#include "../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"

#include "window_framework.h"
#include "object.h"
#include "camera.h"


class Graphics {
	private:
		Object object;
		Camera camera;
		
	public:
		Graphics();
		~Graphics();
<<<<<<< Updated upstream
		static void create(int, char**);
		static void initalization();
		static void error_callback(int, const char*);
		static void key_callback(GLFWwindow*);
		static void draw(GLFWwindow*, int, unsigned int);
		static void handleResize(int, int);
		static void updateWindow(int);
		static void mouse_movement(int, int);
		void load_image(const char*);
		static void perspective_gl(double, double, double, double);
		static void util_compat_gluLookAt(float, float, float, float, float, float, float, float, float);
		double get_key_sensitivity()const;
		void set_key_sensitivity(double);
		double get_mouse_sensitivity()const;
		void set_mouse_sensitivity(double);
		const char* get_vertex_shader()const;
		const char* get_fragment_shader()const;
		static void framebuffer_size_callback(GLFWwindow*, int, int);
		int getWidth();
		int getHeight();
=======
		//void start_program(int, char**);
		void initialize();
		void draw();
		void terminate();
>>>>>>> Stashed changes
};


#endif
