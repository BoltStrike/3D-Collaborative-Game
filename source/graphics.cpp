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
#include "../glad/glad.h"
#include "../freeglut-MinGW-3.0.0-1/include/GL/freeglut.h"

#include <cmath>
#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


// The ONLY global object
Graphics graphics;

Graphics::Graphics () {
	window_width = 1280;
	window_height = 720;
	key_sensitivity = 0.05;
	mouse_sensitivity = 0.1;

	num_buffers = 1;
	//buffer_ids = new unsigned int[num_buffers];
	
}


Graphics::~Graphics () {
	delete [] data;
	//delete [] buffer_ids;
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
	//graphics.load_image("texture.bmp");
	//graphics.buffer();
	
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
	Vector3D position=graphics.geometry.get_position();
	Vector3D offset=graphics.geometry.get_offset();
	double angle = graphics.geometry.get_angle();
	double pitch = graphics.geometry.get_pitch();
    double yaw = graphics.geometry.get_yaw();
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_PROJECTION);
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
    
	// Camera motion
	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(yaw, 0.0, 1.0, 0.0);
	glTranslatef(offset.x, offset.y, offset.z);
	glTranslatef(0.0, -1.0, -5.0);

	//graphics.buffers[0].Draw();
	
	// Ground
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(20, 0, 20);
	glVertex3f(20, 0, -20);
	glVertex3f(-20, 0, -20);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(20, 0, 20);
	glVertex3f(-20, 0, 20);
	glVertex3f(-20, 0, -20);
	glEnd();

    // Create the 3D cube

    // BACK
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.3, 0.2);
    glVertex3f(position.x, -position.y, position.z);
    glVertex3f(position.x, position.y, position.z);
    glVertex3f(-position.x, position.y, position.z);
    glVertex3f(-position.x, -position.y, position.z);
    glEnd();

    // FRONT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.5, 0.0);
    glVertex3f(-position.x, position.y, -position.z);
    glVertex3f(-position.x, -position.y, -position.z);
    glVertex3f(position.x, -position.y, -position.z);
    glVertex3f(position.x, position.y, -position.z);
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-position.x, -position.y, -position.z);
    glVertex3f(-position.x, -position.y, position.z);
    glVertex3f(-position.x, position.y, position.z);
    glVertex3f(-position.x, position.y, -position.z);
    glEnd();


    // RIGHT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(position.x, -position.y, -position.z);
    glVertex3f(position.x, -position.y, position.z);
    glVertex3f(position.x, position.y, position.z);
    glVertex3f(position.x, position.y, -position.z);
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.0, 0.0);
    glVertex3f(position.x, position.y, position.z);
    glVertex3f(-position.x, position.y, position.z);
    glVertex3f(-position.x, position.y, -position.z);
    glVertex3f(position.x, position.y, -position.z);
    glEnd();


    // BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.0, 0.3);
    glVertex3f(-position.x, -position.y, -position.z);
    glVertex3f(-position.x, -position.y, position.z);
    glVertex3f(position.x, -position.y, position.z);
    glVertex3f(position.x, -position.y, -position.z);
    glEnd();


	

    glFlush();
    glutSwapBuffers();
    std::cout << "Draw complete" << std::endl;
}


void Graphics::perspective_gl( double fovY, double aspect, double zNear, double zFar )
{
    const double pi = 3.1415926535897932384626433832795;
    double fW, fH;

    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}


void Graphics::handleResize (int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective_gl(45.0, (double)width / (double)height, 1.0, 200.0);
	graphics.window_width = width;
	graphics.window_height = height;
	
}


void Graphics::updateWindow () {
	double sens_key = graphics.get_key_sensitivity();
	Vector3D offset = graphics.geometry.get_offset();
	if (graphics.geometry.get_keyboard_state('w')) {
		graphics.geometry.set_offset(offset.add(Vector3D(0.0,0.0,-sens_key)));
	}
	if (graphics.geometry.get_keyboard_state('a')) {
		graphics.geometry.set_offset(offset.add(Vector3D(-sens_key,0.0,0.0)));
	}
	if (graphics.geometry.get_keyboard_state('s')) {
		graphics.geometry.set_offset(offset.add(Vector3D(0.0,0.0,sens_key)));
	}
	if (graphics.geometry.get_keyboard_state('d')) {
		graphics.geometry.set_offset(offset.add(Vector3D(sens_key,0.0,0.0)));
	}
	if (graphics.geometry.get_keyboard_state('q')) {
		graphics.geometry.set_offset(offset.add(Vector3D(0.0,sens_key,0.0)));
	}
	if (graphics.geometry.get_keyboard_state('e')) {
		graphics.geometry.set_offset(offset.add(Vector3D(0.0,-sens_key,0.0)));
	}
	// ESCAPE key is ASCII code 27
	if (graphics.geometry.get_keyboard_state(27)) {
		glutLeaveMainLoop();
	}
	
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_UP)) {
		graphics.geometry.set_pitch(graphics.geometry.get_pitch()+sens_key);
	}
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_LEFT)) {
		graphics.geometry.set_yaw(graphics.geometry.get_yaw()-sens_key);
	}
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_DOWN)) {
		graphics.geometry.set_pitch(graphics.geometry.get_pitch()-sens_key);
	}
	if (graphics.geometry.get_special_keyboard_state(GLUT_KEY_RIGHT)) {
		graphics.geometry.set_yaw(graphics.geometry.get_yaw()+sens_key);
	}
	
	glutPostRedisplay();
	//glutTimerFunc(25, updateWindow, 0);
}


void Graphics::keyboard (unsigned char key, int x, int y) {
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
	// ESCAPE key is ASCII code 27
	else if (key == 27) {
		graphics.geometry.set_keyboard_state(27, true);
		glutPostRedisplay();
	}
}

void Graphics::keyboard_up (unsigned char key, int x, int y) {
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
	// ESCAPE key is ASCII code 27
	else if (key == 27) {
		graphics.geometry.set_keyboard_state(27, false);
		glutPostRedisplay();
	}
}

void Graphics::special_keyboard (int key, int x, int y) {
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
	double sens_mouse = graphics.get_mouse_sensitivity();
	double w = graphics.window_width;
	double h = graphics.window_height;
	graphics.geometry.adjust_view(x, y, w, h, sens_mouse);
	if (x <= w/4 || x >= w*3/4) {
		glutWarpPointer(w/2, y);
	}
	if (y <= h/4 || y >= h*3/4) {
		glutWarpPointer(x, h/2);
	}
}

void Graphics::load_image (const char * imagepath) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
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

	/*
	glGenTexture(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);


	//maybe? -Answer: No
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2); 

	#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

glBindTexture(GL_TEXTURE_2D, texture);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
*/
}


double Graphics::get_key_sensitivity () const {
	return key_sensitivity;
}


void Graphics::set_key_sensitivity (double new_key_sensitivity) {
	key_sensitivity = new_key_sensitivity;
}


double Graphics::get_mouse_sensitivity () const {
	return mouse_sensitivity;
}


void Graphics::set_mouse_sensitivity (double new_mouse_sensitivity) {
	mouse_sensitivity = new_mouse_sensitivity;
}


void Graphics::buffer () {
	glGenBuffers(num_buffers, buffer_ids);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_ids[0]);


	/*
	unsigned int numVertices = 4;
	

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

	buffers[0].glBegin(GL_QUADS);
	buffers[0].glColor3f(1.0, 0.0, 0.0);
	buffers[0].glVertex3f(20.0, 5.0, 20.0);
	
	buffers[0].glColor3f(0.0, 1.0, 0.0);
	buffers[0].glVertex3f(-20.0, 5.0, 20.0);
	
	buffers[0].glColor3f(0.0, 1.0, 1.0);
	buffers[0].glVertex3f(-20.0, 5.0, -20.0);
	
	buffers[0].glColor3f(1.0, 0.0, 1.0);
	buffers[0].glVertex3f(20.0, 5.0, -20.0);
	buffers[0].glEnd();
	
	glBindBuffer(GL_ARRAY_BUFFER, bufA);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufB);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, (char*)0);
	glColorPointer(3, GL_FLOAT, 0, (char*)(3*sizeof(GLfloat)*numVertices));
	glDrawElements(GL_QUADS, 1, GL_UNSIGNED_INT, (char*)0);
	*/
}

