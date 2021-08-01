#ifndef INTERNAL_PHYSICS_H
#define INTERNAL_PHYSICS_H

/* This file includes all of the includes that the physics engine needes
 * This is for external libraries (math,vectors,ect.)
 * This may include some constants
 * This may include helper functions/macros
*/

#include "../../glm/glm.hpp"
#include "../generic/program_log.h"
#include <Math.h>

#define TINNY_FLOAT_DELTA 0.000001f

	bool checkLineSegmentPlane(glm::vec3,glm::vec3,glm::vec3,glm::vec3,glm::vec3*);
	
//need to fix to allow for a tiny bit of error
inline bool floatsAreEqual(float a, float b){
	return (b>(a-TINNY_FLOAT_DELTA))&&(b<(a+TINNY_FLOAT_DELTA));
}
inline bool isZero(float a){
	return a==0;
}
	//inline float getPointToLineDistance(glm::vec3,glm::vec3,glm::vec3);
	//inline bool between0and1(float);
inline float getPointToLineDistance(glm::vec3 point,glm::vec3 lineVec,glm::vec3 linePoint){
	return glm::length(glm::cross((linePoint-point), lineVec))/glm::length(lineVec);
}
inline bool isBetween0and1(float a){
	return (a>=0)&&(a<=1);
}
inline bool isZero(glm::vec3 v){
	return isZero(v.x)&&isZero(v.y)&&isZero(v.z);
}
//a bunch on iline functions.
//they are predominatly to make code more readable

//distance between two points:
//use glm::distance(P,Q) or glm::length(P-Q)

//distance squared between two points: (saves flops when posible)
inline float distanceSquared(glm::vec3 P, glm::vec3 Q){
	glm::vec3 temp=P-Q;
	return glm::dot(temp,temp);
}

//distance between two lines:
inline float lineToLineDistance(glm::vec3 P1, glm::vec3 P2, glm::vec3 Q1, glm::vec3 Q2){
	glm::vec3 N=glm::cross(P2-P1,Q2-Q1);
	if(!isZero(N)){
		return abs(glm::dot(N,P1-Q1)/glm::length(N));
	}else{
		return glm::length(glm::cross(P1-Q1,P2-P1))/glm::length(P2-P1);
	}
}
//distance between two lines and the closest points:
inline float lineToLineDistance(glm::vec3 P1, glm::vec3 P2, glm::vec3 Q1, glm::vec3 Q2, glm::vec3* P3, glm::vec3* Q3, bool* pointsModified){
	glm::vec3 N=glm::cross(P2-P1,Q2-Q1);
	if((*pointsModified=!isZero(N))){
		glm::vec3 NP=glm::cross(P2-P1,N);
		glm::vec3 NQ=glm::cross(Q2-Q1,N);
		*P3=P1+(glm::dot(Q1-P1,NQ)/glm::dot(P2-P1,NQ))*(P2-P1);
		*Q3=Q1+(glm::dot(P1-Q1,NP)/glm::dot(Q2-Q1,NP))*(Q2-Q1);
		return abs(glm::dot(N,P1-Q1)/glm::length(N));
	}else{
		return glm::length(glm::cross(P1-Q1,P2-P1))/glm::length(P2-P1);
	}
}
//distance between two line segments:
inline float lineToLineDistance(glm::vec3 P1, glm::vec3 P2, glm::vec3 Q1, glm::vec3 Q2, bool* valid){
	glm::vec3 N=glm::cross(P2-P1,Q2-Q1);
	if(isZero(N)){
		glm::vec3 NP=glm::cross(P2-P1,N);
		glm::vec3 NQ=glm::cross(Q2-Q1,N);
		*valid=isBetween0and1(glm::dot(Q1-P1,NQ)/glm::dot(P2-P1,NQ))&&isBetween0and1(glm::dot(P1-Q1,NP)/glm::dot(Q2-Q1,NP));
		return abs(glm::dot(N,P1-Q1)/glm::length(N));
	}else{
		*valid=false;
		return glm::length(glm::cross(P1-Q1,P2-P1))/glm::length(P2-P1);
	}
}
//distance between two line segments and the closest points:
inline float lineToLineDistance(glm::vec3 P1, glm::vec3 P2, glm::vec3 Q1, glm::vec3 Q2, glm::vec3* P3, glm::vec3* Q3, bool* pointsModified, bool* valid){
	glm::vec3 N=glm::cross(P2-P1,Q2-Q1);
	if((*pointsModified=!isZero(N))){
		glm::vec3 NP=glm::cross(P2-P1,N);
		glm::vec3 NQ=glm::cross(Q2-Q1,N);
		float a=glm::dot(Q1-P1,NQ)/glm::dot(P2-P1,NQ);
		float b=glm::dot(P1-Q1,NP)/glm::dot(Q2-Q1,NP);
		*P3=P1+a*(P2-P1);
		*Q3=Q1+b*(Q2-Q1);
		*valid=isBetween0and1(a)&&isBetween0and1(b);
		return abs(glm::dot(N,P1-Q1)/glm::length(N));
	}else{
		*valid=false;
		return glm::length(glm::cross(P1-Q1,P2-P1))/glm::length(P2-P1);
	}
}


//distance between point and line
inline float pointToLineDistance(glm::vec3 P,glm::vec3 Q1,glm::vec3 Q2){
	glm::vec3 N1=glm::cross(P-Q1,Q2-Q1);
	return glm::length(N1)/glm::length(Q2-Q1);
}
//distance between point and line with the closest point on the line
inline float pointToLineDistance(glm::vec3 P,glm::vec3 Q1,glm::vec3 Q2,glm::vec3* Q3){
	/*glm::vec3 N1=glm::cross(P-Q1,Q2-Q1);
	glm::vec3 N2=glm::cross(Q2-Q1,N1);
	float d=glm::length(N1)/glm::length(Q2-Q1);
	*Q3=P-d*glm::normalize(N2);
	return d;*/
	glm::vec3 A=P-Q1;
	glm::vec3 B=Q2-Q1;
	float d=glm::length(A-(glm::dot(A,B)*B));
	*Q3=Q1-(glm::dot(A,B)*B);
	return d;
}
//distance between point and line segment
inline float pointToLineDistance(glm::vec3 P,glm::vec3 Q1,glm::vec3 Q2,bool* valid){
	/*glm::vec3 N1=glm::cross(P-Q1,Q2-Q1);
	glm::vec3 N2=glm::cross(Q2-Q1,N1);
	float d=glm::length(N1)/glm::length(Q2-Q1);
	glm::vec3 Q3=P-d*glm::normalize(N2);
	*valid=isBetween0and1(glm::length(Q3-Q1)/glm::length(Q2-Q1));
	program_log("    P=");
	program_log(P);
	program_log("\n");
	program_log("    Q1=");
	program_log(Q1);
	program_log("\n");
	program_log("    Q2=");
	program_log(Q2);
	program_log("\n");
	program_log("    N1=");
	program_log(N1);
	program_log("\n");
	program_log("    N2=");
	program_log(N2);
	program_log("\n");
	program_log("    d="+std::to_string(d)+"\n");
	program_log("    Q3=");
	program_log(Q3);
	program_log("\n");
	return d;*/
	glm::vec3 A=P-Q1;
	glm::vec3 B=Q2-Q1;
	float d=glm::length(A-(glm::dot(A,B)*B));
	*valid=isBetween0and1(glm::dot(A,B));
	return d;
}
//distance between point and line segment and the closest point on the line
inline float pointToLineDistance(glm::vec3 P,glm::vec3 Q1,glm::vec3 Q2,glm::vec3* Q3,bool* valid){
	/*glm::vec3 N1=glm::cross(P-Q1,Q2-Q1);
	glm::vec3 N2=glm::cross(Q2-Q1,N1);
	float d=glm::length(N1)/glm::length(Q2-Q1);
	*Q3=P-d*glm::normalize(N2);
	*valid=isBetween0and1(glm::length((*Q3)-Q1)/glm::length(Q2-Q1));
	return d;*/
	glm::vec3 A=P-Q1;
	glm::vec3 B=Q2-Q1;
	float c=glm::dot(A,B);
	float d=glm::length(A-(c*B));
	*valid=isBetween0and1(c);
	*Q3=Q1-(c*B);
	return d;
}

//distance between point and plane
inline float pointToPlaneDistance(glm::vec3 P,glm::vec3 Q1,glm::vec3 Qn){
	return abs(glm::dot(P-Q1,Qn)/glm::length(Qn));
}
//distance between point and plane with closes point on plane
inline float pointToPlaneDistance(glm::vec3 P,glm::vec3 Q1,glm::vec3 Qn,glm::vec3* Q3){
	float d=glm::dot(P-Q1,Qn)/glm::length(Qn);
	*Q3=P-d*glm::normalize(Qn);
	return abs(d);
}

//point of intersection between line and plane
inline glm::vec3 lineAndPlaneIntersection(glm::vec3 P1, glm::vec3 P2, glm::vec3 Q1, glm::vec3 Qn){
	return P1+(P2-P1)*glm::dot(Q1-P1,Qn)/glm::dot(P2-P1,Qn);
}
//point of intersection between line segment and plane
inline glm::vec3 lineAndPlaneIntersection(glm::vec3 P1, glm::vec3 P2, glm::vec3 Q1, glm::vec3 Qn,bool* valid){
	float param=glm::dot(Q1-P1,Qn)/glm::dot(P2-P1,Qn);
	*valid=isBetween0and1(param);
	return P1+(P2-P1)*param;;
}

#endif