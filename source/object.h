/*****************************************************************************
** File: object.h
** Project: 3D Collaborative Game
** Author: Andrew Johnson
** Date Created: 1 August 2020
** Description: Holds all the functions for the Object class
*****************************************************************************/


#ifndef OBJECT_H
#define OBJECT_H

#ifndef _GLAD_
#define _GLAD_
#include "../glad/glad.h"
#endif

#include <cmath>
#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Object {
	private:
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
		float vertices[9] = {
    	    -0.5f, -0.5f, 0.0f, // left  
    	     0.5f, -0.5f, 0.0f, // right 
    		 0.0f,  0.5f, 0.0f  // top   
    	}; 
		int shaderProgram;
		unsigned int VAO;
		unsigned int VBO;

		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
		unsigned int texture;
	public:
		Object();
		~Object();
		int initialize();
		void draw();
		void deallocate();
		void load_image(const char*);
};


#endif
