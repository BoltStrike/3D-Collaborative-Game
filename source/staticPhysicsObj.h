#ifndef STATIC_PHYSICS_OBJ_H
#define STATIC_PHYSICS_OBJ_H

#include "Vector3D.h"
#include "collider.h"
class StaticPhysicsObj: public PhysicsObj{
	virtual CollisionTypes uponCollision();
};
#endif
