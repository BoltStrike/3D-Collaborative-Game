#include "planeCollider.h"
/*PlaneCollider::PlaneCollider(){
	
}
/*PlaneCollider::~PlaneCollider(){
	
}*/
PlaneCollider::PlaneCollider(glm::vec3 pA,glm::vec3 pB,glm::vec3 pC,glm::vec3 pD,glm::vec3 n):Collider(ColliderType::plane,std::fmax(glm::length(pA-pC),glm::length(pB-pD))){
	this->pointA=pA;
	this->pointA=pA;
	this->pointA=pA;
	this->pointA=pA;
	this->normal=n; //will assume this has length of 1
	this->area=glm::length(glm::cross(pB-pA,pC-pA));
}

bool PlaneCollider::checkCollision(Collider* oCol){
	//check each of the lines
	if(oCol->checkLine(pointA,pointB)) return true;
	if(oCol->checkLine(pointB,pointC)) return true;
	if(oCol->checkLine(pointC,pointD)) return true;
	if(oCol->checkLine(pointD,pointA)) return true;
	//do the secondary check
	return oCol->secondaryEdgeCheck(this);
}
bool PlaneCollider::checkLine(glm::vec3 q1,glm::vec3 q2){
	glm::vec3 collisionPoint;
	if(!checkLineSegmentPlane(q1,q2,this->normal,this->pointA,&collisionPoint)) return false;
	//perform area check
	float areaSumX2 =glm::length(glm::cross(collisionPoint-pointA,pointB-pointA));
	areaSumX2+=glm::length(glm::cross(collisionPoint-pointB,pointC-pointB));
	areaSumX2+=glm::length(glm::cross(collisionPoint-pointC,pointD-pointC));
	areaSumX2+=glm::length(glm::cross(collisionPoint-pointD,pointA-pointD));
	return floatsAreEqual(areaSumX2,area*2);
}
bool PlaneCollider::checkLine(glm::vec3,glm::vec3,float){ //cylider line
	//TODO
	return false;
}
bool PlaneCollider::checkPoint(glm::vec3 point){
	//perform area check
	float areaSumX2 =glm::length(glm::cross(point-pointA,pointB-pointA));
	areaSumX2+=glm::length(glm::cross(point-pointB,pointC-pointB));
	areaSumX2+=glm::length(glm::cross(point-pointC,pointD-pointC));
	areaSumX2+=glm::length(glm::cross(point-pointD,pointA-pointD));
	return floatsAreEqual(areaSumX2,area*2);
}
bool PlaneCollider::checkPoint(glm::vec3 point,float rad){ //spheare
	//check distance to inf plane
	//assumeing glm::length(this->normal)=1; as it should
	float dist=glm::dot(point-this->pointA,this->normal);
	if(abs(dist)>rad)return false;
	
	//check closest point area
	//find closest point
	glm::vec3 collisionPoint=point-(dist*this->normal);
	//find the area
	float areaSumX2 =glm::length(glm::cross(collisionPoint-pointA,pointB-pointA));
	areaSumX2+=glm::length(glm::cross(collisionPoint-pointB,pointC-pointB));
	areaSumX2+=glm::length(glm::cross(collisionPoint-pointC,pointD-pointC));
	areaSumX2+=glm::length(glm::cross(collisionPoint-pointD,pointA-pointD));
	if(floatsAreEqual(areaSumX2,area*2)) return true;
	
	//check edges
	//get line to point distance
	//check if on a line segment
	dist=getPointToLineDistance(point,pointB-pointA,pointA);
	if(dist<=rad && between0and1(glm::dot(pointA,pointB-pointA)/(glm::length(pointB-pointA)*glm::length(pointB-pointA)))) return true;
	dist=getPointToLineDistance(point,pointC-pointB,pointB);
	if(dist<=rad && between0and1(glm::dot(pointB,pointC-pointB)/(glm::length(pointC-pointB)*glm::length(pointC-pointB)))) return true;
	dist=getPointToLineDistance(point,pointD-pointC,pointC);
	if(dist<=rad && between0and1(glm::dot(pointC,pointD-pointC)/(glm::length(pointD-pointC)*glm::length(pointD-pointC)))) return true;	
	dist=getPointToLineDistance(point,pointA-pointD,pointD);
	if(dist<=rad && between0and1(glm::dot(pointD,pointA-pointD)/(glm::length(pointA-pointD)*glm::length(pointA-pointD)))) return true;
	//check points
	if(glm::length(point-pointA)<=rad)return true;
	if(glm::length(point-pointB)<=rad)return true;
	if(glm::length(point-pointC)<=rad)return true;
	if(glm::length(point-pointD)<=rad)return true;
	return false;
}
void PlaneCollider::applyPosRot(glm::vec3 pos,glm::vec3 rot){
	return;
}
bool PlaneCollider::secondaryEdgeCheck(Collider* oCol){
	if(oCol->checkLine(pointA,pointB)) return true;
	if(oCol->checkLine(pointB,pointC)) return true;
	if(oCol->checkLine(pointC,pointD)) return true;
	return false;
}
	