#include "dynamicTestBox.h"
DynamicTestBox::DynamicTestBox(){
	DynamicPhysicsObj();
}
DynamicTestBox::DynamicTestBox(Vector3D* pos, Vector3D* size):DynamicPhysicsObj(pos, new Vector3D(0.0,4.0,0.0), new Vector3D(0.0,0.0,0.0), new Vector3D(0.0,0.0,0.0), new Vector3D(0.0,0.0,0.0), new Vector3D(0.0,-10.0,0.0), new BoxCollider(size->x,size->y,size->z))
{
	std::cout<<"pos (box):";
	position->display();
	gravity->display();
	std::cout<<std::endl;
}
DynamicTestBox::~DynamicTestBox(){

}

CollisionType DynamicTestBox::uponCollision(){
	std::cout<<"Collision has ocurred"<<std::endl;
	CollisionType stop;
	return stop;
}