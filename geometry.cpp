/*****************************************************************************
** File: geometry.cpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 12 July 2020
** Description: Holds all the functions for the Geometry class
*****************************************************************************/


#include "geometry.hpp"
#include <cmath>

#ifndef PI
#define PI 3.14159265
#endif

Geometry::Geometry () {
	pos = new double[3];
	offset = new double[3];
	keyboard_state = new bool[128];
	special_keyboard_state = new bool[128];
	mouse_x = 0;
	mouse_y = 0;
	pos[0] = 0.3;
	pos[1] = 0.6;
	pos[2] = 0.9;
	offset[0] = 0.0;
	offset[1] = 0.0;
	offset[2] = 0.0;
	angle = 0.0;
	pitch = 0.0; // up and down
	yaw = 0.0; // side to side
}


Geometry::~Geometry () {
	delete [] pos;
	delete [] offset;
	delete [] keyboard_state;
	delete [] special_keyboard_state;
}


double* Geometry::get_position () const {
	return pos;
}


void Geometry::set_position (double x, double y, double z) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}


double Geometry::get_angle () const {
	return angle;
}


void Geometry::set_angle (double new_angle) {
	angle = new_angle;
}


double* Geometry::get_offset () const {
	return offset;
}


void Geometry::set_offset (double x, double y, double z) {
	offset[0] = x;
	offset[1] = y;
	offset[2] = z;
}


bool Geometry::get_keyboard_state (int index) const {
	return keyboard_state[index];
}


void Geometry::set_keyboard_state (int index, bool state) {
	keyboard_state[index] = state;
}


bool Geometry::get_special_keyboard_state (int index) const {
	return special_keyboard_state[index];
}


void Geometry::set_special_keyboard_state (int index, bool state) {
	special_keyboard_state[index] = state;
}

int Geometry::get_mouse_x () const {
	return mouse_x;
}

int Geometry::get_mouse_y () const {
	return mouse_y;
}


double Geometry::get_pitch () const {
	return pitch;
}

void Geometry::set_pitch (double new_pitch) {
	pitch = new_pitch;
}

double Geometry::get_yaw () const {
	return yaw;
}

void Geometry::set_yaw (double new_yaw) {
	yaw = new_yaw;
}

void Geometry::adjust_view (int x, int y, int width, int height) {
	if (x <= width/4 || x >= width*3/4) {
		x = width/2;
		mouse_x = width/2;
	}
	if (y <= height/4 || y >= height*3/4) {
		y = height/2;
		mouse_y = height/2;
	}
	yaw += 0.01*(x-mouse_x);
	pitch += 0.01*(y-mouse_y);
	mouse_x = x;
	mouse_y = y;
}


