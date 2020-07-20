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
		constexpr static int ESC = 27;
		Geometry geometry;
		int window_id;
		int window_width;
		int window_height;
		
		bool loaded;
		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
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
};


#endif
