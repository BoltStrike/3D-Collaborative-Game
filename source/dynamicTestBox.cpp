#include "dynamicTestBox.h"
DynamicTestBox::DynamicTestBox(){
	DynamicPhysicsObj();
}
DynamicTestBox::DynamicTestBox(Vector3D pos, Vector3D size){
	DynamicPhysicsObj(pos, Vector3D(0.0,4.0,0.0), Vector3D(0.0,0.0,0.0), Vector3D(0.0,0.0,0.0), Vector3D(0.0,0.0,0.0), Vector3D(0.0,-10.0,0.0), BoxCollider(size.x,size.y,size.z));
	std::cout<<"pos (box):";
	position.display();
	std::cout<<std::endl;
}

CollisionType DynamicTestBox::uponCollision(){
	std::cout<<"Collision has ocurred"<<std::endl;
	CollisionType stop;
	return stop;
}