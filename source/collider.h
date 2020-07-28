#ifndef COLLIDER_H
#define	COLLIDER_H

#include "Vector3D.h"
#include "colliderType.h"

class Collider{
	protected:
	ColliderType type;
	Collider(ColliderType);
	public:
	Collider();
	virtual ~Collider();
	ColliderType getColliderType();
	virtual int checkCollision(Vector3D,Vector3D,Collider*,Vector3D,Vector3D);
};

#endif
