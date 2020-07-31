/*****************************************************************************
** File: geometry.cpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 12 July 2020
** Description: Holds all the functions for the Geometry class
*****************************************************************************/


#include "geometry.h"
#include <cmath>

Geometry::Geometry () {
	keyboard_state = new bool[128];
	special_keyboard_state = new bool[128];
	for (int i=0; i < 128; i++) {
		keyboard_state[i] = false;
		special_keyboard_state[i] = false;
	}
	mouse_x = 0;
	mouse_y = 0;
	pos=Vector3D(0.3,0.6,0.9);
	offset=Vector3D(0.0,0.0,0.0);
	pitch = 0.0; // up and down
	yaw = 0.0; // side to side
}


Geometry::~Geometry () {
	delete [] keyboard_state;
	delete [] special_keyboard_state;
}


Vector3D Geometry::get_position () const {
	return pos;
}


void Geometry::set_position (Vector3D pos) {
	this->pos=pos;
}


Vector3D Geometry::get_offset () const {
	return offset;
}


void Geometry::set_offset (Vector3D offset) {
	this->offset=offset;
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

void Geometry::adjust_view (int x, int y, int width, int height, double sens) {
	if (x <= width/4 || x >= width*3/4) {
		x = width/2;
		mouse_x = width/2;
	}
	if (y <= height/4 || y >= height*3/4) {
		y = height/2;
		mouse_y = height/2;
	}
	yaw += sens*(x-mouse_x);
	pitch += sens*(y-mouse_y);
	mouse_x = x;
	mouse_y = y;
}


