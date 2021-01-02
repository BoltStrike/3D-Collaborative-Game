#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "collider.h"
#include "internalPhysics.h"

const int BoxColliderLineList[12][2]={
			{0,1},
			{0,2},
			{0,4},
			{3,2},
			{3,1},
			{3,7},
			{5,1},
			{5,4},
			{5,7},
			{6,2},
			{6,4},
			{6,7}};

class BoxCollider:public Collider{
	private:
		glm::vec3* pointList;
	public:
		BoxCollider();
		~BoxCollider();
		BoxCollider(float,float,float);
		BoxCollider(glm::vec3*);
		BoxCollider(const BoxCollider& other);
		
		glm::vec3* getPointList();
		
		bool checkCollision(Collider*);
		//There will be functions for resolving collision, though they are not yet implimented or used
	
	//stuff for check parts of a collision
	public:
		//There may be too many functions here
		bool checkLine(glm::vec3,glm::vec3);
		bool checkLine(glm::vec3,glm::vec3,float); //cylider line
		bool checkPoint(glm::vec3);
		bool checkPoint(glm::vec3,float); //spheare
		bool secondaryEdgeCheck(Collider*);
		
		//this applies a position and rotation vector to the collider
		void applyPosRot(glm::vec3,glm::vec3);
	private:
		bool checkLineVsFace(glm::vec3,glm::vec3,int,int,int,int);
		bool checkPointVsFace(glm::vec3,float,int,int,int,int);
};


#endif