/*****************************************************************************
** File: camera.cpp
** Project: 3D Collaborative Game
** Date Created: 1 August 2020
** Description: Holds all the functions for the Camera class
*****************************************************************************/



#include "camera.h"


Camera::Camera () {
	location = Vector3D(0.0, 0.0, 0.0);
	pitch = 2.0;
	yaw = 2.0;
	key_sensitivity = 0.1;
}

Camera::~Camera () {

}

void Camera::draw () {

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
	//std::cout << "Location: (" << location.x << ", " << location.y << ", " << location.z << ")" << std::endl;
}
