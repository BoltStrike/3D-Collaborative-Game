/*****************************************************************************
** File: graphics.hpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 12 July 2020
** Description: Holds all the functions for the Graphics class
*****************************************************************************/


#include "graphics.hpp"
#include "geometry.hpp"

// the GLUT and OpenGL libraries have to be linked correctly
#include <windows.h>
#include "glad/glad.h"

//#include "glut-3.7.6/glut.h"
//#include "freeglut-3.2.1/include/GL/freeglut.h"
#include "GLUT-MinGW-3.7.6-6/include/glut.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#ifndef PI
#define PI 3.14159265
#endif


// The ONLY global object
Graphics graphics;

Graphics::Graphics () {
	window_width = 1280;
	window_height = 720;
	loaded = false;
}


Graphics::~Graphics () {
	
}


void Graphics::create (int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(graphics.window_width, graphics.window_height);
    glutInitWindowPosition(100, 100);
    graphics.window_id = glutCreateWindow("OpenGL - Creating a triangle");
    
	if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        system("pause");
        return;
    }
    std::cout << "Initialized OpenGL context" << std::endl;
    
	initalization();
	
	glutDisplayFunc(drawTriangle);
	glutReshapeFunc(handleResize);
	glutIdleFunc(updateWindow);
	// Update the window every 25 milliseconds
	//glutTimerFunc(25, updateWindow, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(special_keyboard);
	glutSpecialUpFunc(special_keyboard_up);
	glutMotionFunc(mouse_movement);
	glutPassiveMotionFunc(mouse_movement);
	glutSetCursor(GLUT_CURSOR_NONE);
	std::cout << "Initalization complete, starting glutMainLoop()" << std::endl;
    glutMainLoop();
}


void Graphics::initalization () {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	
	// Set the background color
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	
}


void Graphics::drawTriangle () {
	double *position = graphics.geometry.get_position();
	double angle = graphics.geometry.get_angle();
	double *offset = graphics.geometry.get_offset();
	double x = position[0];
	double y = position[1];
	double z = position[2];
	double offset_x = offset[0];
	double offset_y = offset[1];
	double offset_z = offset[2];
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	// Reset transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Add an ambient light
    GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add a positioned light
    GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    double pitch = graphics.geometry.get_pitch();
    double yaw = graphics.geometry.get_yaw();
    
    // Camera Motion
    gluLookAt(offset_x, offset_y, offset_z,
    		  offset_x+cos(yaw)*cos(pitch), offset_y-sin(yaw)*cos(pitch), offset_z+sin(pitch),
    		  0.0, 0.0, 1.0);
    glTranslatef(-cos(yaw)*cos(pitch), sin(yaw)*cos(pitch), -sin(pitch));

	glTranslatef(-5.0, 0.0, -1.0);
	
	// Ground
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(20, 20, 0);
	glVertex3f(20, -20, 0);
	glVertex3f(-20, -20, 0);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(20, 20, 0);
	glVertex3f(-20, 20, 0);
	glVertex3f(-20, -20, 0);
	glEnd();

    // Create the 3D cube

    // BACK
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.3, 0.2);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, -y, z);
    glEnd();

    // FRONT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.5, 0.0);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);
    glEnd();


    // RIGHT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(x, -y, -z);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.0, 0.0);
    glVertex3f(x, y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);
    glEnd();


    // BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.0, 0.3);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);
    glEnd();

    glFlush();
    glutSwapBuffers();
    std::cout << "Draw complete" << std::endl;
}


void Graphics::handleResize (int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
	graphics.window_width = width;
	graphics.window_height = height;
}


void Graphics::updateWindow () {
	double *offset = graphics.geometry.get_offset();
	if (graphics.geometry.get_keyboard_state('w')) {
		graphics.geometry.set_offset(offset[0], offset[1]+0.1, offset[2]);
	}
	if (graphics.geometry.get_keyboard_state('a')) {
		graphics.geometry.set_offset(offset[0] + 0.1, offset[1], offset[2]);
	}
	if (graphics.geometry.get_keyboard_state('s')) {
		graphics.geometry.set_offset(offset[0], offset[1]-0.1, offset[2]);
	}
	if (graphics.geometry.get_keyboard_state('d')) {
		graphics.geometry.set_offset(offset[0] - 0.1, offset[1], offset[2]);
	}
	if (graphics.geometry.get_keyboard_state('q')) {
		graphics.geometry.set_offset(offset[0], offset[1], offset[2]+0.1);
	}
	if (graphics.geometry.get_keyboard_state('e')) {
		graphics.geometry.set_offset(offset[0], offset[1], offset[2]-0.1);
	}
	if (graphics.geometry.get_keyboard_state(ESC)) {
		//glutLeaveMainLoop();
		exit(0);
	}
	
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_UP)) {
		graphics.geometry.set_pitch(graphics.geometry.get_pitch()+0.01);
	}
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_LEFT)) {
		graphics.geometry.set_yaw(graphics.geometry.get_yaw()-0.01);
	}
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_DOWN)) {
		graphics.geometry.set_pitch(graphics.geometry.get_pitch()-0.01);
	}
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_RIGHT)) {
		graphics.geometry.set_yaw(graphics.geometry.get_yaw()+0.01);
	}
	
	double *position = graphics.geometry.get_position();
	double x = position[0];
	double y = position[1];
	double z = position[2];
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glutPostRedisplay();
	//glutTimerFunc(25, updateWindow, 0);
}


void Graphics::keyboard (unsigned char key, int x, int y) {
	double *offset = graphics.geometry.get_offset();
	if (key == 'w' || key == 'W') {
		graphics.geometry.set_keyboard_state('w', true);
		glutPostRedisplay();
	}
	else if (key == 'a' || key == 'A') {
		graphics.geometry.set_keyboard_state('a', true);
		glutPostRedisplay();
	}
	else if (key == 's' || key == 'S') {
		graphics.geometry.set_keyboard_state('s', true);
		glutPostRedisplay();
	}
	else if (key == 'd' || key == 'D') {
		graphics.geometry.set_keyboard_state('d', true);
		glutPostRedisplay();
	}
	else if (key == 'q' || key == 'Q') {
		graphics.geometry.set_keyboard_state('q', true);
		glutPostRedisplay();
	}
	else if (key == 'e' || key == 'E') {
		graphics.geometry.set_keyboard_state('e', true);
		glutPostRedisplay();
	}
	else if (key == ESC) {
		graphics.geometry.set_keyboard_state(ESC, true);
		glutPostRedisplay();
	}
}

void Graphics::keyboard_up (unsigned char key, int x, int y) {
	double *offset = graphics.geometry.get_offset();
	if (key == 'w' || key == 'W') {
		graphics.geometry.set_keyboard_state('w', false);
		glutPostRedisplay();
	}
	else if (key == 'a' || key == 'A') {
		graphics.geometry.set_keyboard_state('a', false);
		glutPostRedisplay();
	}
	else if (key == 's' || key == 'S') {
		graphics.geometry.set_keyboard_state('s', false);
		glutPostRedisplay();
	}
	else if (key == 'd' || key == 'D') {
		graphics.geometry.set_keyboard_state('d', false);
		glutPostRedisplay();
	}
	else if (key == 'q' || key == 'Q') {
		graphics.geometry.set_keyboard_state('q', false);
		glutPostRedisplay();
	}
	else if (key == 'e' || key == 'E') {
		graphics.geometry.set_keyboard_state('e', false);
		glutPostRedisplay();
	}
	else if (key == ESC) {
		graphics.geometry.set_keyboard_state(ESC, false);
		glutPostRedisplay();
	}
}

void Graphics::special_keyboard (int key, int x, int y) {
	double *offset = graphics.geometry.get_offset();
	if (key == GLUT_KEY_UP) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_UP, true);
	}
	else if (key == GLUT_KEY_LEFT) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_LEFT, true);
	}
	else if (key == GLUT_KEY_DOWN) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_DOWN, true);
	}
	else if (key == GLUT_KEY_RIGHT) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_RIGHT, true);
	}
}

void Graphics::special_keyboard_up (int key, int x, int y) {
	double *offset = graphics.geometry.get_offset();
	if (key == GLUT_KEY_UP) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_UP, false);
	}
	else if (key == GLUT_KEY_LEFT) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_LEFT, false);
	}
	else if (key == GLUT_KEY_DOWN) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_DOWN, false);
	}
	else if (key == GLUT_KEY_RIGHT) {
		graphics.geometry.set_special_keyboard_state(GLUT_KEY_RIGHT, false);
	}
}


void Graphics::mouse_movement (int x, int y) {
	graphics.geometry.adjust_view(x, y, graphics.window_width, graphics.window_height);
	if (x <= graphics.window_width/4 || x >= graphics.window_width*3/4) {
		glutWarpPointer(graphics.window_width/2, y);
	}
	if (y <= graphics.window_height/4 || y >= graphics.window_height*3/4) {
		glutWarpPointer(x, graphics.window_height/2);
	}

}

void Graphics::load_image (const char * imagepath) {
	FILE * file = fopen(imagepath,"rb");
	if (!file) {
		printf("Image could not be opened\n"); 
		return;
	}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    	printf("Not a correct BMP file\n");
    	return;
	}
	if ( header[0]!='B' || header[1]!='M' ){
    	printf("Not a correct BMP file\n");
    	return;
	}
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	
	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) {
		imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	}
	if (dataPos==0) {
		dataPos=54; // The BMP header is done that way
	}
	
	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	//Everything is in memory now, the file can be closed
	fclose(file);
	loaded = true;
}

