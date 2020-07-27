#ifndef PHYSICS_OBJ_H
#define PHYSICS_OBJ_H

#include "physics.h"
#include "collider.h"
class PhysicsObj{
	protected:
	Vector3D position;
	Vector3D rotattion;
	Collider collider;
	
	PhysicsObj();
	PhysicsObj(Vector3D,Vector3D,Collider);
	
	public:
	Vector3D getPosition();
	Vector3D getRotation();
	Collider* getCollider();
	bool checkCollision(Collider*,Vector3D,Vector3D);
	virtual CollisionTypes uponCollision();
};
#endif
