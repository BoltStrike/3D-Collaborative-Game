#include "sphereCollider.h"
#include <iostream>

SphereCollider::SphereCollider():Collider(ColliderType::sphere){
	this->rad=1.0;
}
SphereCollider::~SphereCollider(){
}
SphereCollider::SphereCollider(double rad):Collider(ColliderType::sphere){
	this->rad=rad;
}
double SphereCollider::getRad(){
	return this->rad;
}

int SphereCollider::checkCollision(Vector3D* posA,Vector3D* angA,Collider* b,Vector3D* posB,Vector3D* angB){
	Vector3D vectBetweenCenters=*posA-*posB;
	double distBetweenCenters=vectBetweenCenters.mag();
	std::cout<<"\tDist: "<<distBetweenCenters<<std::endl;
	switch(b->getColliderType()){
		case ColliderType::sphere:
			return (distBetweenCenters<=(this->rad+((SphereCollider*)b)->getRad()))?1:0;
		default:
			return 0;
		
	}
	return 0;
}