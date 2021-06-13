#include "internalPhysics.h"
bool checkLineSegmentPlane(glm::vec3 linePointA,glm::vec3 linePointB,glm::vec3 planeNormal,glm::vec3 planePoint,glm::vec3* collisionPointOut){
	//this checks if the two poitns are on opisit sides of the plane
	float temp;
	if((temp=(glm::dot(planePoint-linePointA,planeNormal))*glm::dot(planePoint-linePointB,planeNormal))>0) return false;
	//time to find the point of intersection
	glm::vec3 lineVector=linePointB-linePointA;
	float lineParm=temp/glm::dot(lineVector,planeNormal);
	*collisionPointOut=(lineVector*lineParm)+linePointA;
	
	return true;
}