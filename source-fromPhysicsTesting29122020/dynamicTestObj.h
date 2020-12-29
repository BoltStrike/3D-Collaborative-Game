#ifndef DYNAMIC_TEST_OBJ_H
#define DYNAMIC_TEST_OBJ_H

#include "physics.h"
class DynamicTestObj: public DynamicPhysicsObj{
	public:
	std::string name;
	DynamicTestObj();
	DynamicTestObj(std::string,Vector3D*,Collider*);
	virtual ~DynamicTestObj();
	CollisionType uponCollision();
	void dumpInfo();	
};

#endif