#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "collider.h"
#include "Vector3D.h"

class BoxCollider:public Collider{
	private:
	Vector3D normals[3];
	public:
	BoxCollider();//:Collider(ColliderType::box);
	BoxCollider(Vector3D,Vector3D,Vector3D);//:Collider(ColliderType::box);
	BoxCollider(double,double,double);//:Collider(ColliderType::box);
	Vector3D* getNormals();
	bool checkCollision(Vector3D,Vector3D,PhysicsObj*);
};

#endif