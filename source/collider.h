#ifndef COLLIDER_H
#define	COLLIDER_H

#include "colliderType.h"
#include "boxCollider.h"
#include "Vector3D.h"
#include "physicsObj.h"

class Collider{
	protected:
	ColliderType type;
	Collider();
	Collider(ColliderType);
	public:
	ColliderType getColliderType();
	virtual bool checkCollision(Vector3D,Vector3D,PhysicsObj*);
	protected:
	static bool checkCollision(BoxCollider*,Vector3D,Vector3D,BoxCollider*,Vector3D,Vector3D);
	private:
	static bool lineVsBox(Vector3D,Vector3D,Vector3D,Vector3D*,Vector3D);
};

#endif