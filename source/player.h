#ifndef PLAYER_H
#define PLAYER_H

#include "physics.h"

class Player: public DynamicPhysicsObj{
	public:
	Vector3D camPosOffset;
	Vector3D camRotOffset;
	Player();
	~Player();
	Vector3D getCamPos();
	Vector3D getCamRot();
};

#endif