#include "player.h"

Player::Player():DynamicPhysicsObj(new Vector3D(0.0,1.1,0.0),new Vector3D(0.0,0.0,0.0),new Vector3D(0.0,0.0,0.0),new Vector3D(0.0,0.0,0.0),new Vector3D(0.0,0.0,0.0),new Vector3D(0.0,-10.0,0.0),new BoxCollider(1.0,2.0,1.0)){
	this->camPosOffset;
	this->camRotOffset;
}

Player::~Player(){}

Vector3D Player::getCamPos(){
	return this->camPosOffset+*getPosition();
}
Vector3D Player::getCamRot(){
	return this->camRotOffset+*getRotation();
}