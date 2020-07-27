#include "physicsObj.h"

PhysicsObj(){
	this->position=Vector3D(0.0,0.0,0.0);
	this->rotation=Vector3D(0.0,0.0,0.0);
	this->collider=Collider();
}

PhysicsObj::PhysicsObj(Vector3D position, Vector3D rotation, Collider collider){
	this->position=position;
	this->rotation=rotation;
	this->collider=collider;
}

Vector3D PhysicsObj::getPosition(){
	return position;
}
Vector3D PhysicsObj::getRotation(){
	return rotation;
}

Collider* PhysicsObj::getCollider(){
	return &collider;
}
bool PhysicsObj::checkCollision(Collider* otherCollider,Vector3D otherPos,Vector3D otherAng){
	return this->collider.checkCollision(position,rotation,otherCollider,otherPos,otherAng);
}