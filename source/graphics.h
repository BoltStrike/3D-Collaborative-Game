/******************************************************************************
** File: graphics.hpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 12 July 2020
** Description: Creates an object to handle all OpenGL and GLUT window 
** operations and commands
******************************************************************************/


#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "geometry.h"
#include "../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"


class Graphics {
	private:
		Geometry geometry;
		int window_id;
		int window_width;
		int window_height;
		double key_sensitivity;
		double mouse_sensitivity;
		
		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
		unsigned int texture;

		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
		
	public:
		Graphics();
		~Graphics();
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
};


#endif
