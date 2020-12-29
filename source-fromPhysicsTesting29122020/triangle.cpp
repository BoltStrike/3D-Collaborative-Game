#include "triangle.h"

//there is no way to write a valid default constructor
Triangle::Triangle(){
	this->pointA=0;
	this->pointB=0;
	this->pointC=0;
	this->normal=Vector3D();
	this->areaX2=0;
}
Triangle::Triangle(int pointA, int pointB, int pointC, Vector3D normal, Vector3D* points){
	this->pointA=pointA;
	this->pointB=pointB;
	this->pointC=pointC;
	this->normal=normal;
	this->areaX2=V3Dcross(points[pointA]-points[pointB],points[pointC]-points[pointB]).mag();
}
Triangle::Triangle(int pointA, int pointB, int pointC, Vector3D* points){
	this->pointA=pointA;
	this->pointB=pointB;
	this->pointC=pointC;
	this->normal=V3Dcross(points[pointA]-points[pointB],points[pointC]-points[pointB]);
	this->areaX2=normal.mag();
}
void Triangle::rotateNormal(Vector3D* rot){
	normal=V3Drotate(normal,*rot);
}
bool Triangle::checkAgainstLine(Vector3D line, Vector3D* linePointA, Vector3D* linePointB, Vector3D* points){
	double temp;
	Vector3D point;
	double pointArea;
	Vector3D diffrence=(*linePointB)-(*linePointA);
	double maxT=(line.x==0)?((line.y==0)?(diffrence.z/line.z):(diffrence.y/line.y)):(diffrence.x/line.x);
	temp=V3Ddot(points[pointA]-(*linePointA),normal)/V3Ddot(normal,line);
	if((maxT<0)?(temp>=maxT && temp<=0):(temp>=0 && temp<=maxT)){
		point=points[pointA]+line.scale(temp);
		pointArea=V3Dcross(point-points[pointA],point-points[pointB]).mag();
		if(pointArea>areaX2)return false;
		pointArea+=V3Dcross(point-points[pointB],point-points[pointC]).mag();
		if(pointArea>areaX2)return false;
		pointArea=V3Dcross(point-points[pointC],point-points[pointA]).mag();
		if(pointArea>areaX2)return false;
		return true;
	}
	return false;
}
int Triangle::getPoint(int num){
	switch(num){
		case 0:
		return this->pointA;
		case 1:
		return this->pointB;
		case 2:
		return this->pointC;
	}
	return 0;
}