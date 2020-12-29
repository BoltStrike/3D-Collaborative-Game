#include "dynamicPhysicsObj.h"
#include <IOstream>
DynamicPhysicsObj::DynamicPhysicsObj():PhysicsObj()
{
	this->velocity=new Vector3D(0.0,0.0,0.0);
	this->acceleration=new Vector3D(0.0,0.0,0.0);
	this->angularVelocity=new Vector3D(0.0,0.0,0.0);
	this->gravity=new Vector3D(0.0,0.0,0.0);
}

DynamicPhysicsObj::DynamicPhysicsObj(Vector3D* position, Vector3D* rotation, Collider* collider):PhysicsObj(position,rotation,collider)
{
	this->velocity=new Vector3D(0.0,0.0,0.0);
	this->acceleration=new Vector3D(0.0,0.0,0.0);
	this->angularVelocity=new Vector3D(0.0,0.0,0.0);
	this->gravity=new Vector3D(0.0,0.0,0.0);
}

DynamicPhysicsObj::DynamicPhysicsObj(Vector3D* position, Vector3D* velocity, Vector3D* acceleration, Vector3D* rotation, Vector3D* angularVelocity, Vector3D* gravity, Collider* collider):PhysicsObj(position,rotation,collider)
{
	this->velocity=velocity;
	this->acceleration=acceleration;
	this->angularVelocity=angularVelocity;
	this->gravity=gravity;
	/*std::cout<<"pos (dyn):";
	position->display();
	gravity->display();
	std::cout<<std::endl;*/
}

DynamicPhysicsObj::~DynamicPhysicsObj(){
	delete velocity;
	delete acceleration;
	delete angularVelocity;
	delete gravity;
}


void DynamicPhysicsObj::update(PhysicsObj** collisionList,long collisionListSize,long currentNum,double deltaT){
	int tmp=0;
	//update all the values;
	*velocity=*velocity+acceleration->scale(deltaT)+gravity->scale(deltaT);
	*position=*position+velocity->scale(deltaT);
	*rotation=*rotation+angularVelocity->scale(deltaT);
	if(!velocity->isZero() || !angularVelocity->isZero()){
		//check for collision
		long i=0;
		for(long i=0;i<collisionListSize;i++){
			if(i!=currentNum){
				if((tmp=checkCollision(collisionList[i]->getCollider(),collisionList[i]->getPosition(),collisionList[i]->getRotation()))!=0){
					//std::cout<<tmp;
					this->uponCollision();
					collisionList[i]->uponCollision();
				}
			}
		}
	}
}

CollisionType DynamicPhysicsObj::uponCollision() {
	CollisionType stop;
	return stop;
}