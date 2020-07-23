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

#include "geometry.hpp"


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
	public:
		Graphics();
		~Graphics();
		static void create(int, char**);
		static void initalization();
		static void drawTriangle();
		static void handleResize(int, int);
		static void updateWindow();
		static void keyboard(unsigned char, int, int);
		static void keyboard_up(unsigned char, int, int);
		static void special_keyboard(int, int, int);
		static void special_keyboard_up(int, int, int);
		static void mouse_movement(int, int);
		void load_image(const char*);
		static void perspective_gl(double, double, double, double);
		static void util_compat_gluLookAt(float, float, float, float, float, float, float, float, float);
		double get_key_sensitivity()const;
		void set_key_sensitivity(double);
		double get_mouse_sensitivity()const;
		void set_mouse_sensitivity(double);
};


#endif
