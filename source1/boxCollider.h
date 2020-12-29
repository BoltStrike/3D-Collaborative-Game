#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "collider.h"
#include "Vector3D.h"

class BoxCollider:public Collider{
	private:
	Vector3D* normals[3];
	public:
	BoxCollider();//:Collider(ColliderType::box);
	BoxCollider(Vector3D*,Vector3D*,Vector3D*);//:Collider(ColliderType::box);
	BoxCollider(double,double,double);//:Collider(ColliderType::box);
	virtual ~BoxCollider();
	Vector3D** getNormals();
	int checkCollision(Vector3D*,Vector3D*,Collider*,Vector3D*,Vector3D*);
	private:
	static int checkCollision(BoxCollider*,Vector3D*,Vector3D*,BoxCollider*,Vector3D*,Vector3D*);
};
	static bool lineVsBox(Vector3D,Vector3D,Vector3D,Vector3D*,Vector3D* );
#endif