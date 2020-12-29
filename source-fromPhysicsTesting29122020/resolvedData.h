#ifndef RESOLVED_DATA_H
#define RESOLVED_DATA_H

#include "Vector3D.h"
#include <cmath>
class ResolvedData{
	public:
	Vector3D newPos;
	Vector3D normal;
	Vector3D collisionPoint;
	double collisionTime;
	
	ResolvedData();
	ResolvedData(Vector3D,Vector3D,Vector3D,double);
	
};

#endif