#ifndef GLOBALS_PHYSICS_H
#define GLOBALS_PHYSICS_H

#include "Vector3D.h"

#define PHYSICS_STATS true
#define DEBUG_PHYSICS 0

#if(PHYSICS_STATS)
	long long numberOfObjectsChecked=0;
	long long numberOfFullChecksSaved=0;
	long long numberOfTrianglesChecked=0;
#endif

#endif