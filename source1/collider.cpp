#include "collider.h"
Collider::Collider(){
	type=ColliderType::none;
}
Collider::~Collider(){

}
Collider::Collider(ColliderType ct){
	type=ct;
}
ColliderType Collider::getColliderType(){
	return type;
}
int Collider::checkCollision(Vector3D* a,Vector3D* b,Collider* c,Vector3D* d,Vector3D* e){
	return 0;
}
