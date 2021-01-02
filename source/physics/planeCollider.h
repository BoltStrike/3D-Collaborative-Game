#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

#include "collider.h"
#include "internalPhysics.h"

class PlaneCollider: public Collider{
	private:
		glm::vec3 pointA;
		glm::vec3 pointB;
		glm::vec3 pointC;
		glm::vec3 pointD;
		glm::vec3 normal;
		float area;
	public:
		//PlaneCollider();
		//~PlaneCollider();
		//PlaneCollider(const PlaneCollider &old);
		PlaneCollider(glm::vec3,glm::vec3,glm::vec3,glm::vec3,glm::vec3);
		bool checkCollision(Collider*);
	public:
		bool checkLine(glm::vec3,glm::vec3);
		bool checkLine(glm::vec3,glm::vec3,float); //cylider line
		bool checkPoint(glm::vec3);
		bool checkPoint(glm::vec3,float); //spheare
		void applyPosRot(glm::vec3,glm::vec3);
		bool secondaryEdgeCheck(Collider*);
};

#endif