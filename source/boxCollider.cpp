#include "boxCollider.h"

BoxCollider::BoxCollider():Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=Vector3D(1.0,0.0,0.0);
	normals[1]=Vector3D(0.0,1.0,0.0);
	normals[2]=Vector3D(0.0,0.0,1.0);
}
BoxCollider::BoxCollider(double w,double l,double h):Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=Vector3D(w,0.0,0.0);
	normals[1]=Vector3D(0.0,l,0.0);
	normals[2]=Vector3D(0.0,0.0,h);
}
BoxCollider::BoxCollider(Vector3D a,Vector3D b,Vector3D c):Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=a;
	normals[1]=b;
	normals[2]=c;
}
Vector3D* BoxCollider::getNormals(){
	return normals;
}
bool BoxCollider::checkCollision(Vector3D pos,Vector3D rot,PhysicsObj* po){
	switch(po->getCollider().getColliderType()){
		case ColliderType::box:
			return Collider->checkCollision(this,pos,rot,(BoxCollider) po->getCollider(),po->getPosition(),po->getRotation());
		
	}
}