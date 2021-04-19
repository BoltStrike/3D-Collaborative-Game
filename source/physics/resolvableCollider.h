#ifndef RESOLVABLE_COLLIDER_H
#define RESOLVABLE_COLLIDER_H

#include "internalPhysics.h"

#include "colliderType.h"

#include "collider.h"

class ResolvableCollider:public Collider{
	protected:
		float boundingRad;
		//default type will be spheare, beacuse the one datapoint
		//needed is already in the parrent class
		ColliderType type;
		
		//variables for resolving collisions
		//all pointers so object has compleate control
		float* stepup;	//for walking on terain how far can the object step up without jumping
		glm::vec3* gravity;	//pointer to gravity, so it is controled by the object
	public:
		~ResolvableCollider();
		ResolvableCollider(ColliderType,float,float*,gravity*);
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
	//the good stuff
	//resolving collisions
	public:
		//things that need to be passed in:
		//	list of colliders
		//	motion paramiters:
		//		position
		//		velocity
		//		acceleration
		//		delta time
		//		force/driven
		//things that need to come out:
		//	motion params:
		//	
		
		//rotation is not included for simplicity, and this only works with sphear and vertical pill
};

#endif