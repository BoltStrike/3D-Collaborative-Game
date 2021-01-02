#ifndef COLLIDER_H
#define CLOOIDER_H

#include "internalPhysics.h"

#include "colliderType.h"

class Collider{
	protected:
		float boundingRad;
		//default type will be spheare, beacuse the one datapoint
		//needed is already in the parrent class
		ColliderType type;
		//List of impimented types:
		//
	public:
		Collider();
		~Collider();
		Collider(ColliderType,float);
		float getBoundingRad();
		ColliderType getType();
		
		//this is the entry function for detecting collision
		//always put its own pos&rot then the other's pos&rot;
		bool checkCollision(glm::vec3,glm::vec3,Collider*,glm::vec3,glm::vec3);
		virtual bool checkCollision(Collider*);
		//There will be functions for resolving collision, though they are not yet implimented or used
	
	//stuff for check parts of a collision
	public:
		//There may be too many functions here
		virtual bool checkLine(glm::vec3,glm::vec3);
		virtual bool checkLine(glm::vec3,glm::vec3,float); //cylider line
		virtual bool checkPoint(glm::vec3);
		virtual bool checkPoint(glm::vec3,float); //spheare
		virtual bool secondaryEdgeCheck(Collider*);
		
		//this applies a position and rotation vector to the collider
		virtual void applyPosRot(glm::vec3,glm::vec3);
	
};

#endif