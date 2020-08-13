/*****************************************************************************
** File: graphics.cpp
** Project: 3D Collaborative Game
** Date Created: 12 July 2020
** Description: Holds all the functions for the Graphics class
*****************************************************************************/


#include "graphics.h"


Graphics::Graphics () {

}

Graphics::~Graphics () {


}

void Graphics::draw () {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < num_objects; i++) {
		objects_array[i].draw(*camera);
	}
    
    glFlush();
}

void Graphics::handle_input (bool *keyboard_state) {
	camera->handle_input(keyboard_state);
}

void Graphics::handle_mouse (double x, double y, double w, double h) {
	camera->handle_mouse(x, y, w, h);
}


void Graphics::initialize () {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	camera = new Camera();
	num_objects = 1;
	objects_array = new Object[num_objects];
	//objects_array[0].load("assets/export_triangle/");
	//objects_array[1].load("assets/export_triangle2/");
	objects_array[0].load("assets/cube/");
}


void Graphics::terminate () {
	for (int i = 0; i < num_objects; i++) {
		objects_array[i].deallocate();
	}
	delete [] objects_array;
	delete camera;
}

