#ifndef DYNAMIC_TEST_BOX_H
#define DYNAMIC_TEST_BOX_H

#include "physics.h"
class DynamicTestBox: public DynamicPhysicsObj{
	public:
	DynamicTestBox();
	DynamicTestBox(Vector3D*,Vector3D*);
	virtual ~DynamicTestBox();
	CollisionType uponCollision();	
};

#endif