#ifndef RESOLVABLE_COLLIDER_H
#define RESOLVABLE_COLLIDER_H

#include "internalPhysics.h"

#include "colliderType.h"

#include "collider.h"

#include <vector>

class ResolvableCollider:public Collider{
	protected:
		float boundingRad;
		//default type will be spheare, beacuse the one datapoint
		//needed is already in the parrent class
		ColliderType type;
		
		//pill specifi variables
		float pillRad;
		float lineLength;
		//indicate the two points
		glm::vec3 P1;
		glm::vec3 P2;
		
		//variables for resolving collisions
		//all pointers so object has compleate control
		float stepup;	//for walking on terain how far can the object step up without jumping
		float gravity;	//pointer to gravity, so it is controled by the object
		//all items act from the center of the mass
		glm::vec3 velocity;
		glm::vec3 acceleration;
		//no angular items
	public:
		~ResolvableCollider();
		ResolvableCollider(ColliderType,float,glm::vec3);
		ResolvableCollider(float rad, float pillRad, float lineLength, float stepup, float gravity, glm::vec3 position);
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
		void timeUpdate(float deltaT,std::vector<Collider*>* staticColliders,std::vector<ResolvableCollider*>* dynamicColliders,int selfIndex);
		
		//rotation is not included for simplicity, and this only works with sphear and vertical pill
	public:
		void setStepup(float);
		float getStepup();
		void setGravity(float);
		float getGravity();
		//motion paramiters
		void setPosition(glm::vec3);
		glm::vec3 getPosition();
		void setRotation(glm::vec3);
		glm::vec3 getRotation();
		void setVelocity(glm::vec3);
		glm::vec3 getVelocity();
		void setAcceleration(glm::vec3);
		glm::vec3 getAcceleration();
};

#endif