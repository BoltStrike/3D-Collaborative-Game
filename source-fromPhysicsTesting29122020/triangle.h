#ifndef TRIANGLE
#define TRIANGLE

#include "globalPhysics.h"

class Triangle{
	public:
	int pointA;
	int pointB;
	int pointC;
	Vector3D normal;
	double areaX2;
	
	Triangle();
	Triangle(int pointA, int pointB, int pointC, Vector3D normal, Vector3D* points);
	Triangle(int pointA, int pointB, int pointC, Vector3D* points);
	void rotateNormal(Vector3D* rot);
	bool checkAgainstLine(Vector3D line, Vector3D* linePointA, Vector3D* linePointB, Vector3D* points);
	int getPoint(int);
};

#endif