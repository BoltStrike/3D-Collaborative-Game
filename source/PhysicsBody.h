#include "Vector3D.h"
#ifndef PhysicsBody_h
#define PhysicsBody_h
class PhysicsBody {
	private:
		Vector3D position;
		Vector3D velocity;
		Vector3D acceleration;
		Vector3D rotation;
		Vector3D angularVelocity;
		bool hasMaxSpeed;
		double maxSpeedSqured;
	public:
		PhysicsBody(){
			position = Vector3D(0.0f,0.0f,0.0f);
			velocity = Vector3D(0.0f,0.0f,0.0f);
			acceleration = Vector3D(0.0f,0.0f,0.0f);
			rotation = Vector3D(0.0f,0.0f,0.0f);
			angularVelocity = Vector3D(0.0f,0.0f,0.0f);
			hasMaxSpeed = false;
			maxSpeedSqured = 0.0f;
		}
	
		void physicsUpdate(double deltaT);
		
		Vector3D getPosition(){
			return position;
		}
		void setPosition(Vector3D newVal){
			position=newVal;
		}
		Vector3D getVelocity(){
			return velocity;
		}
		void setVelocity(Vector3D newVal){
			velocity=newVal;
		}
		Vector3D getAcceleration(){
			return acceleration;
		}
		void setAcceleration(Vector3D newVal){
			acceleration=newVal;
		}
		Vector3D getRotation(){
			return rotation;
		}
		void setRotation(Vector3D newVal){
			rotation=newVal;
		}
		Vector3D getAngularVelocity(){
			return angularVelocity;
		}
		void setAngularVelocity(Vector3D newVal){
			angularVelocity=newVal;
		}
		void setMaxSpeed(double speed){
			hasMaxSpeed=true;
			maxSpeedSqured=speed*speed;
		}
		void removeMaxSpeed(){
			hasMaxSpeed=false;
		}
};

#endif
