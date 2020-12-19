/******************************************************************************
** File: graphics.hpp
** Project: 3D Collaborative Game
** Date Created: 12 July 2020
** Description: Creates an object to handle all OpenGL and GLUT window 
** operations and commands
******************************************************************************/


#ifndef GRAPHICS_H
#define GRAPHICS_H

// the GLFW and OpenGL libraries have to be linked correctly
#ifndef _GLAD_
#define _GLAD_
#include "../glad/glad.h"
#endif

#include "object.h"
#include "camera.h"


class Graphics {
	private:
		unsigned int num_objects;
		Object *objects_array;
		Camera *camera;
		
	public:
		Graphics();
		~Graphics();
		void initialize();
		void draw();
		void handle_input(bool*);
		void handle_mouse(double, double, double, double);
		void terminate();
};


#endif
