#include "staticTestBox.h"
StaticTestBox::StaticTestBox(){
	StaticPhysicsObj();
}
StaticTestBox::StaticTestBox(Vector3D pos, Vector3D size){
	StaticPhysicsObj(pos, Vector3D(0.0,0.0,0.0), BoxCollider(size.x,size.y,size.z));
}

CollisionType StaticTestBox::uponCollision(){
	CollisionType stop;
	return stop;
}