/*****************************************************************************
** File: camera.h
** Project: 3D Collaborative Game
** Author: Andrew Johnson
** Date Created: 1 August 2020
** Description: Defines a camera in the OpenGL context
*****************************************************************************/


#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3D.h"
#ifndef GLAD_H
#define GLAD_H
#include "../glad/glad.h"
#endif
#include <iostream>
#include <cmath>

class Camera {
	private:
		double pitch;
		double yaw;
		double key_sensitivity;
		double mouse_sensitivity;
		double mouse_x;
		double mouse_y;
	public:
		Vector3D location;
		Camera();
		~Camera();
		void handle_input(bool*);
		void handle_mouse(double, double ,double, double);
};


#endif
