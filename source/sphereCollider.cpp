#include "sphereCollider.h"

SphereCollider::SphereCollider(){
	this->rad=1.0;
}
SphereCollider::~SphereCollider(){
}
SphereCollider::SphereCollider(double rad){
	this->rad=rad;
}
double SphereCollider::getRad(){
	return this->rad;
}

int SphereCollider::checkCollision(Vector3D* posA,Vector3D* angA,Collider* b,Vector3D* posB,Vector3D* angB){
	Vector3D vectBetweenCenters=*posA-*posB;
	switch(b->getColliderType()){
		case ColliderType::sphere:
			return (vectBetweenCenters.mag()>(this->rad+((SphereCollider*)b)->getRad()))?1:0;
		default:
			return 0;
		
	}
	return 0;
}