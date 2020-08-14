/*****************************************************************************
** File: camera.cpp
** Project: 3D Collaborative Game
** Date Created: 1 August 2020
** Description: Holds all the functions for the Camera class
*****************************************************************************/



#include "camera.h"


Camera::Camera () {
	location = Vector3D(1.0, 1.0, 1.0);
	pitch = 2.0;
	yaw = 2.0;
	key_sensitivity = 0.1;
	mouse_sensitivity = 0.001;
	mouse_x = 0.0;
	mouse_y = 0.0;
}

Camera::~Camera () {

}

void Camera::handle_input (bool *key) {
	if (key['w']) {
		location = location + Vector3D(0.0, 0.0, key_sensitivity);
	}
	if (key['a']) {
		location = location + Vector3D(-key_sensitivity, 0.0, 0.0);
	}
	if (key['s']) {
		location = location + Vector3D(0.0, 0.0, -key_sensitivity);
	}
	if (key['d']) {
		location = location + Vector3D(key_sensitivity, 0.0, 0.0);
	}
	if (key['q']) {
		location = location + Vector3D(0.0, key_sensitivity, 0.0);
	}
	if (key['e']) {
		location = location + Vector3D(0.0, -key_sensitivity, 0.0);
	}
}


void Camera::handle_mouse (double x, double y, double w, double h) {
	if (x <= w/4 || x >= w*3/4) {
		x = w/2;
		mouse_x = w/2;
	}
	if (y <= h/4 || y >= h*3/4) {
		y = h/2;
		mouse_y = h/2;
	}
	
	yaw += mouse_sensitivity*(x-mouse_x);
	pitch += mouse_sensitivity*(y-mouse_y);
	
	if (mouse_x != x || mouse_y != y) {
		mouse_x = x;
		mouse_y = y;
		//double magnitude = sqrt(location.x*location.x+location.z*location.z);
		//location = Vector3D(magnitude*cos(yaw), -magnitude*sin(pitch), magnitude*-sin(yaw));
	}
}
