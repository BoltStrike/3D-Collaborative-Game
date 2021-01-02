#ifndef INTERNAL_PHYSICS_H
#define INTERNAL_PHYSICS_H

/* This file includes all of the includes that the physics engine needes
 * This is for external libraries (math,vectors,ect.)
 * This may include some constants
 * This may include helper functions/macros
*/

#include "../../glm/glm.hpp"
#include <Math.h>

	bool checkLineSegmentPlane(glm::vec3,glm::vec3,glm::vec3,glm::vec3,glm::vec3*);
	bool floatsAreEqual(float a, float b);
	//inline float getPointToLineDistance(glm::vec3,glm::vec3,glm::vec3);
	//inline bool between0and1(float);
inline float getPointToLineDistance(glm::vec3 point,glm::vec3 lineVec,glm::vec3 linePoint){
	return glm::length(glm::cross((linePoint-point), lineVec))/glm::length(lineVec);
}
inline bool between0and1(float a){
	return (a>=0)&&(a<=1);
}

#endif