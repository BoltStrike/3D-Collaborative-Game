#ifndef PHYSICS_OBJ_H
#define PHYSICS_OBJ_H

#include "Vector3D.h"
#include "collider.h"
#include "collisionType.h"
#include "boxCollider.h"
class PhysicsObj{
	protected:
	Vector3D position;
	Vector3D rotation;
	Collider collider;
	public:
	PhysicsObj();
	PhysicsObj(Vector3D,Vector3D,Collider);
	
	public:
	Vector3D getPosition();
	Vector3D getRotation();
	Collider* getCollider();
	bool checkCollision(Collider*,Vector3D,Vector3D);
	virtual CollisionType uponCollision();
};
#endif
