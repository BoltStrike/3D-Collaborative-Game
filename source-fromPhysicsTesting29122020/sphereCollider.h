#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "collider.h"
#include "Vector3D.h"

class SphereCollider:public Collider{
	private:
	double rad;
	public:
	SphereCollider();
	virtual ~SphereCollider();
	SphereCollider(double);
	double getRad();
	int checkCollision(Vector3D*,Vector3D*,Collider*,Vector3D*,Vector3D*);
};

#endif