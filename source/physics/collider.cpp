#include "collider.h"
Collider::Collider(){
	this->boundingRad=0.0f;
	this->type=ColliderType::sphere;
}
Collider::~Collider(){
	
}
Collider::Collider(ColliderType type,float boundingRad,glm::vec3 pos, glm::vec3 rot){
	this->boundingRad=boundingRad;
	this->type=type;
	this->setRotation(rot);
	this->setPosition(pos);
}
float Collider::getBoundingRad(){
	return this->boundingRad;
}
ColliderType Collider::getType(){
	return this->type;
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
bool Collider::secondaryEdgeCheck(Collider* oCol){
	return false;
}
float Collider::resolveVertPillVert(glm::vec3 point1,glm::vec3 point2,float rad,float maxLineParam){
	return 0.0;
}

void Collider::setPosition(glm::vec3 pos){
	this->position=pos;
}
glm::vec3 Collider::getPosition(){
	return this->position;
}
void Collider::setRotation(glm::vec3 rot){
	this->rotation=rot;
}
glm::vec3 Collider::getRotation(){
	return this->rotation;
}
	