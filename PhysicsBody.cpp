#include "PhysiscsBody.h"
using namespace std;
void PhysiscsBody::physicsUpdate(double deltaT){
	//update the translational information
	velocity=velocity.add(acceleration.scale(deltaT));
	//sheck for speed limits
	if(hasMaxSpeed && velocity.magSqu()>=maxSpeedSqu){
		//cap the speed, but keep the direction
		velocity=velocity.scale(velocity.magSqu()/maxSpeedSqu);
	}
	//update positon
	position=position.add(velocity.scale(delatT));
	//update rotation
	rotation=rotation.add(angularVelocity(delataT));
}