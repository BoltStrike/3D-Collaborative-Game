/*****************************************************************************
** File: object.h
** Project: 3D Collaborative Game
** Author: Andrew Johnson
** Date Created: 1 August 2020
** Description: Holds all the functions for the Object class
*****************************************************************************/


#ifndef OBJECT_H
#define OBJECT_H

#ifndef GLAD_H
#define GLAD_H
#include "../glad/glad.h"
#endif

#include <cmath>
#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "camera.h"

class Object {
	private:
		char *vertexShaderSource;
		char *fragmentShaderSource;
		float *vertices;
		int shaderProgram;
		int offsetLocation;
		int perspectiveMatrixUnif;
		float theMatrix[16];
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
		Object(const char*);
		~Object();
		int initialize();
		void draw(Camera);
		void deallocate();
		char* load_file(const char*);
		void load_image(const char*);
};


#endif
