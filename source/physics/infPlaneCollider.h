#ifndef INF_PLANE_COLLIDER_H
#define INF_PLANE_COLLIDER_H

#include "collider.h"
#include "internalPhysics.h"

class InfPlaneCollider: public Collider{
	private:
		glm::vec3 point;
		glm::vec3 normal;
	public:
		InfPlaneCollider();
		~InfPlaneCollider();
		InfPlaneCollider(const InfPlaneCollider &old);
		InfPlaneCollider(glm::vec3,glm::vec3);
		bool checkCollision(Collider*);
		glm::vec3 getPoint();
		glm::vec3 getNormal();
	public:
		bool checkLine(glm::vec3,glm::vec3);
		bool checkLine(glm::vec3,glm::vec3,float); //cylider line
		bool checkPoint(glm::vec3);
		bool checkPoint(glm::vec3,float); //spheare
		void applyPosRot(glm::vec3,glm::vec3);
		bool secondaryEdgeCheck(Collider*);
};

#endif