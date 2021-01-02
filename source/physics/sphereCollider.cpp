#include "sphereCollider.h"
SphereCollider::SphereCollider():Collider(){
	this->pos=glm::vec3(0.0f,0.0f,0.0f);
}
SphereCollider::~SphereCollider(){
	
}
SphereCollider::SphereCollider(float rad):Collider(ColliderType::sphere,rad){
	this->pos=glm::vec3(0.0f,0.0f,0.0f);
}

bool SphereCollider::checkCollision(Collider* oCol){
	return oCol->checkPoint(this->pos,Collider::boundingRad);
}
//all functions return false, use child classes;
bool SphereCollider::checkLine(glm::vec3 q1,glm::vec3 q2){
	//find shortest distance between pos and line
	float shortestDist=glm::length(glm::cross(pos-q1,q2-q1))/glm::length(q2-q1);
	if(shortestDist>boundingRad) return false;
	//see if it is the line segment
	float a=glm::dot(q2-q1,pos-q1)/(glm::length(q2-q1)*glm::length(q2-q1));
	if(between0and1(a)) return true;
	//check the endpoints of the line segment
	if(glm::length(q1-this->pos)<=boundingRad) return true;
	if(glm::length(q2-this->pos)<=boundingRad) return true;
	return false;
}
bool SphereCollider::checkLine(glm::vec3 q1,glm::vec3 q2,float rad){ //cylider line
	//TODO
	return false;
}
bool SphereCollider::checkPoint(glm::vec3 point){
	return glm::length(point-this->pos)<=boundingRad;
}
bool SphereCollider::checkPoint(glm::vec3 point,float rad){ //spheare
	return glm::length(point-this->pos)<=(boundingRad+rad);
}
void SphereCollider::applyPosRot(glm::vec3 pos,glm::vec3 rot){
	this->pos=pos;
	//no need to account for rotation
}
bool SphereCollider::secondaryEdgeCheck(Collider* oCol){
	return false;
}
	