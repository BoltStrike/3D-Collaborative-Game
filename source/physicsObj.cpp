#include "physicsObj.h"
#include <iostream>
PhysicsObj::PhysicsObj(){
	this->position=new Vector3D(0.0,0.0,0.0);
	this->rotation=new Vector3D(0.0,0.0,0.0);
	this->collider=new BoxCollider(1.0,1.0,1.0);
}

PhysicsObj::PhysicsObj(Vector3D* pos, Vector3D* rot, Collider* col){
	this->position=pos;
	this->rotation=rot;
	this->collider=col;
	std::cout<<"pos:";
	this->position->display();
	std::cout<<std::endl;
}
PhysicsObj::~PhysicsObj(){
	delete position;
	delete rotation;
	delete collider;
}

Vector3D* PhysicsObj::getPosition(){
	return position;
}
Vector3D* PhysicsObj::getRotation(){
	return rotation;
}

Collider* PhysicsObj::getCollider(){
	return collider;
}
bool PhysicsObj::checkCollision(Collider* otherCollider,Vector3D* otherPos,Vector3D* otherAng){
	return this->collider->checkCollision(position,rotation,otherCollider,otherPos,otherAng);
}


CollisionType PhysicsObj::uponCollision() {
	CollisionType stop;
	return stop;
}

