#include "staticTestBox.h"
StaticTestBox::StaticTestBox():StaticPhysicsObj(){
}
StaticTestBox::StaticTestBox(Vector3D* pos, Vector3D* size):StaticPhysicsObj(pos, new Vector3D(0.0,0.0,0.0), new BoxCollider(size->x,size->y,size->z)){
}
StaticTestBox::~StaticTestBox(){}

CollisionType StaticTestBox::uponCollision(){
	CollisionType stop;
	return stop;
}