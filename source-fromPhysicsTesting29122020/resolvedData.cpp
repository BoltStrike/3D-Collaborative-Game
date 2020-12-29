#include "resolvedData.h"
ResolvedData::ResolvedData(){
	newPos=Vector3D();
	normal=Vector3D();
	collisionPoint=Vector3D();
	collisionTime=0.0;
}
ResolvedData::ResolvedData(Vector3D newPos,Vector3D normal,Vector3D collisionPoint,double collisionTime){
	this->newPos=newPos;
	this->normal=normal;
	this->collisionPoint=collisionPoint;
	this->collisionTime=collisionTime;
}