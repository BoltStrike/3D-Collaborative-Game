#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "internalPhysics.h"
#include "collider.h"

class SphereCollider: public Collider{
	private:
		glm::vec3 pos;
	public:
		SphereCollider();
		~SphereCollider();
		SphereCollider(float);
		SphereCollider(float,glm::vec3);
		
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
};

#endif