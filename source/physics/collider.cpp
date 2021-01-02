#include "collider.h"
Collider::Collider(){
	this->boundingRad=0.0f;
	this->type=ColliderType::sphere;
}
Collider::~Collider(){
	
}
Collider::Collider(ColliderType type,float boundingRad){
	this->boundingRad=boundingRad;
	this->type=type;
}
float Collider::getBoundingRad(){
	return this->boundingRad;
}
ColliderType Collider::getType(){
	return this->type;
}
//always put its own pos&rot then the other's pos&rot;
bool Collider::checkCollision(glm::vec3 pos,glm::vec3 rot,Collider* otherCol,glm::vec3 otherPos,glm::vec3 otherRot){
	//check bounding spears
	if(glm::length(pos-otherPos)>(this->getBoundingRad()+otherCol->getBoundingRad())) return false;
	//apply pos and rot
	Collider oCol=*otherCol;
	oCol.applyPosRot(otherPos,otherRot);
	Collider t=*this;
	t.applyPosRot(pos,rot);
	return t.checkCollision(&oCol);
}
bool Collider::checkCollision(Collider* oCol){
	return false;
}
//all functions return false, use child classes;
bool Collider::checkLine(glm::vec3 q1,glm::vec3 q2){
	return false;
}
bool Collider::checkLine(glm::vec3 q1,glm::vec3 q2,float rad){ //cylider line
	return false;
}
bool Collider::checkPoint(glm::vec3 point){
	return false;
}
bool Collider::checkPoint(glm::vec3 point,float rad){ //spheare
	return false;
}
void Collider::applyPosRot(glm::vec3 pos,glm::vec3 rot){
	return;
}
bool Collider::secondaryEdgeCheck(Collider* oCol){
	return false;
}
	