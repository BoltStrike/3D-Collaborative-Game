#ifndef COLLIDER_H
#define COLLIDER_H

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
		glm::vec3 position;
		glm::vec3 rotation;
	public:
		Collider();
		~Collider();
		Collider(ColliderType,float rad,glm::vec3 pos, glm::vec3 rot);
		float getBoundingRad();
		ColliderType getType();
		
		//this is the entry function for detecting collision
		//always put its own pos&rot then the other's pos&rot;
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
	
	//section for collion resalutition functions
	public:
		virtual float resolveVertPillVert(glm::vec3,glm::vec3,float,float);
	public:
		void setPosition(glm::vec3);
		glm::vec3 getPosition();
		void setRotation(glm::vec3);
		glm::vec3 getRotation();
		
};

#endif