#ifndef STATIC_TEST_BOX_H
#define STATIC_TEST_BOX_H

#include "physics.h"
class StaticTestBox: public StaticPhysicsObj{
	public:
	StaticTestBox();
	StaticTestBox(Vector3D*,Vector3D*);
	virtual ~StaticTestBox();
	CollisionType uponCollision();	
};

#endif