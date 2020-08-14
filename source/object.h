/*****************************************************************************
** File: object.h
** Project: 3D Collaborative Game
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
#include "wavefront.h"

class Object {
	private:
		char *vertexShaderSource;
		char *fragmentShaderSource;
		unsigned int num_vertices;
		float *vertices;
		Wavefront verts;
		int shaderProgram;
		int offsetLocation;
		int perspectiveMatrixUnif;
		unsigned int VAO;
		unsigned int VBO[2];
		unsigned int tex;

		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;
		unsigned char * data;
		unsigned int texture;
	public:
		float theMatrix[16];
		Object();
		Object(const char*,Camera*);
		~Object();
		void load(const char*,Camera*);
		void do_shaders(Camera*);
		void create_buffers();
		int initialize(Camera*);
		void draw(Camera);
		void deallocate();
		char* load_file(const char*);
		void load_image(const char*);
};


#endif
