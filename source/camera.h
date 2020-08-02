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
#ifndef _GLAD_
#define _GLAD_
#include "../glad/glad.h"
#endif

class Camera {
	private:
		Vector3D location;
		double pitch;
		double yaw;
	public:
		Camera();
		~Camera();
		void translate(Vector3D);
		void rotate_pitch(double);
		void rotate_yaw(double);
		void draw();
};


#endif
