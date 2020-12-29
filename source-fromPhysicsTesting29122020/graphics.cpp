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
    glClear(GL_COLOR_BUFFER_BIT);
    tri1.draw(camera);
    tri2->draw(camera);
    
    glFlush();
}

void Graphics::handle_input (bool *keyboard_state) {
	camera.handle_input(keyboard_state);
}


void Graphics::initialize () {
	tri1.initialize();
	const char *filepath = "assets/triangle/";
	tri2 = new Object(filepath);
	tri2->initialize();
}


void Graphics::terminate () {
	tri1.deallocate();
	tri2->deallocate();
	delete tri2;
}

