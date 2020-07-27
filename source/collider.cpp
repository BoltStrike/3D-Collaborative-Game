#include "collider.h"
Collider::Collider(){
	type=ColliderType::none;
}
Collider::Collider(ColliderType ct){
	type=ct;
}
ColliderType Collider::getColliderType(){
	return type;
}
