#include "staticPhysicsObj.h"
StaticPhysicsObj::StaticPhysicsObj(){
	PhysicsObj();
}
StaticPhysicsObj::StaticPhysicsObj(Vector3D pos,Vector3D rot,Collider col){
	PhysicsObj(pos,rot,col);
}