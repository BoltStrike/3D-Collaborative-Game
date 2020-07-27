#ifndef DYNAMIC_PHYSICS_OBJ_H
#define DYNAMIC_PHYSICS_OBJ_H

#include "physicsObj.h"
class DynamicPhysicsObj: public PhysicsObj{
	protected:
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D angularVelocity;
	
	DynamicPhysicsObj();
	DynamicPhysicsObj(Vector3D,Vector3D,Collider);
	DynamicPhysicsObj(Vector3D,Vector3D,Vector3D,Vector3D,Vector3D,Collider);
	
	public:
	void update(PhysicsObj*,long,long,double);
};
#endif
