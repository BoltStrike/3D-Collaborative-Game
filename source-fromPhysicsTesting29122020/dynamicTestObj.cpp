#include "dynamicTestObj.h"
DynamicTestObj::DynamicTestObj(){
	DynamicPhysicsObj();
}
DynamicTestObj::DynamicTestObj(std::string name,Vector3D* pos, Collider* col):DynamicPhysicsObj(pos, new Vector3D(0.0,-2.0,0.0), new Vector3D(0.0,0.0,0.0), new Vector3D(0.0,0.0,0.0), new Vector3D(0.0,0.0,0.0), new Vector3D(0.0,-10.0,0.0), col)
{
	this->name=name;
	std::cout<<"pos (box):";
	position->display();
	gravity->display();
	std::cout<<std::endl;
}
DynamicTestObj::~DynamicTestObj(){
	
}

CollisionType DynamicTestObj::uponCollision(){
	std::cout<<"Collision has ocurred with: "<<name<<std::endl;
	CollisionType stop;
	return stop;
}
void DynamicTestObj::dumpInfo(){
	std::cout<<name<<":"<<std::endl;
	std::cout<<"\tPosition: ";
	getPosition()->display();
	std::cout<<std::endl<<"\tVelocity: ";
	velocity->display();
	std::cout<<std::endl;
}