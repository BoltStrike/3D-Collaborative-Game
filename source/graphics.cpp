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
    //camera.draw();
    object.draw();
    glFlush();
}


void Graphics::initialize () {
	object.initialize();
}


void Graphics::terminate () {
	object.deallocate();
}

