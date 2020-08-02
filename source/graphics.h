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
		void initialize();
		void draw();
		void terminate();
};


#endif
