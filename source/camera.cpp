/*****************************************************************************
** File: camera.cpp
** Project: 3D Collaborative Game
** Author: Andrew Johnson
** Date Created: 1 August 2020
** Description: Holds all the functions for the Camera class
*****************************************************************************/



#include "camera.h"


Camera::Camera () {
	location = Vector3D(0.0, 0.0, 0.0);
	double pitch = 0.0;
	double yaw = 0.0;
}

Camera::~Camera () {

}

void Camera::translate (Vector3D offset) {
	location = location + offset;
}

void Camera::rotate_pitch (double offset) {
	pitch += offset;
}

void Camera::rotate_yaw (double offset) {
	yaw += offset;
}

void Camera::draw () {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(yaw, 0.0, 1.0, 0.0);
	glTranslatef(location.x, location.y, location.z);
	glTranslatef(0.0, -1.0, -5.0);
}
