#include "staticTestObj.h"
StaticTestObj::StaticTestObj():StaticPhysicsObj(){
}
StaticTestObj::StaticTestObj(std::string name,Vector3D* pos,Collider* col):StaticPhysicsObj(pos, new Vector3D(0.0,0.0,0.0), col){
	this->name=name;
}
StaticTestObj::~StaticTestObj(){ }

CollisionType StaticTestObj::uponCollision(){
	std::cout<<"Collision has ocurred with: "<<name<<std::endl;
	CollisionType stop;
	return stop;
}
void StaticTestObj::dumpInfo(){
	std::cout<<name<<":"<<std::endl;
	std::cout<<"\tPosition: ";
	getPosition()->display();
	std::cout<<std::endl;
}