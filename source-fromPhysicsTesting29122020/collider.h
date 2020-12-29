#ifndef COLLIDER_H
#define	COLLIDER_H

#include "Vector3D.h"
#include "globalPhysics.h"
#include "colliderType.h"
#include "resolvedData.h"

class Collider{
	protected:
	ColliderType type;
	Collider(ColliderType);
	public:
	Collider();
	virtual ~Collider();
	ColliderType getColliderType();
	virtual int checkCollision(Vector3D*,Vector3D*,Collider*,Vector3D*,Vector3D*);
	virtual ResolvedData fixCollision(Vector3D*,Vector3D*,Vector3D*,Collider*,Vector3D*,Vector3D*);
	static Vector3D collideTwoPlanes(Vector3D,Vector3D,Vector3D,Vector3D);
	static Vector3D collideTwoLines(Vector3D,Vector3D,Vector3D,Vector3D);
};

#endif
