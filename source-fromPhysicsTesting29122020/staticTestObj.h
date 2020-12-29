#ifndef STATIC_TEST_OBJ_H
#define STATIC_TEST_OBJ_H

#include "physics.h"
class StaticTestObj: public StaticPhysicsObj{
	public:
	std::string name;
	StaticTestObj();
	StaticTestObj(std::string,Vector3D*,Collider*);
	virtual ~StaticTestObj();
	CollisionType uponCollision();	
	void dumpInfo();
};

#endif