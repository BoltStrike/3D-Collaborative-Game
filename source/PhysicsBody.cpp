#include "PhysicsBody.h"
using namespace std;
void PhysicsBody::physicsUpdate(double deltaT){
	//update the translational information
	velocity=velocity.add(acceleration.scale(deltaT));
	//sheck for speed limits
	if(hasMaxSpeed && velocity.magSqu()>=maxSpeedSqured){
		//cap the speed, but keep the direction
		velocity=velocity.scale(velocity.magSqu()/maxSpeedSqured);
	}
	//update positon
	position=position.add(velocity.scale(deltaT));
	//update rotation
	rotation=rotation.add(angularVelocity);
}
