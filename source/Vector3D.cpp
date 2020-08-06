//libray for vertor stuff
#include <cmath>
#include "Vector3D.h"
using namespace std;

	Vector3D::Vector3D(double x,double y,double z){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	Vector3D::Vector3D(){
		this->x=0.0;
		this->y=0.0;
		this->z=0.0;
	}
	Vector3D::Vector3D(double* val){
		this->x=val[0];
		this->y=val[1];
		this->z=val[2];
	}
	Vector3D::Vector3D(const Vector3D &obj){
		this->x=obj.x;
		this->y=obj.y;
		this->z=obj.z;
	}
	//returns the magnatude of the vector
double Vector3D::mag(void){
		return sqrt((x*x)+(y*y)+(z*z));
	}

	//returns the magnatude squared of the vector
	//this is computaionaly easer than mag(), but does the same job
	double Vector3D::magSqu(void){
		return (x*x)+(y*y)+(z*z);
	}

	//scales each value by a certian amount
	Vector3D Vector3D::scale(double ammount){
		return Vector3D(x*ammount,y*ammount,z*ammount);
	}

	//returns a unit vector in the direction of it's self
	Vector3D Vector3D::unit(){
		double size=mag();
		return Vector3D(x/size,y/size,z/size);
	}

	//adds a value to it's self
	Vector3D Vector3D::add(Vector3D ammount){
		return Vector3D(x+ammount.x,y+ammount.y,z+ammount.z);
	}
	
	Vector3D Vector3D::operator+(const Vector3D& b){
		return Vector3D(this->x+b.x,this->y+b.y,this->z+b.z);
	}
	Vector3D Vector3D::operator-(const Vector3D& b){
		return Vector3D(this->x-b.x,this->y-b.y,this->z-b.z);
	}
	Vector3D Vector3D::operator-(){
		return Vector3D(-x,-y,-z);
	}
	
	bool Vector3D::isZero(){
		return (x==0)&&(y==0)&&(z==0);
	}

	///dot product
	double V3Ddot(Vector3D a,Vector3D b){
		return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
	}

	//cross prduct
	//|  X   Y   Z  |
	//| a.x a.y a.z |
	//| b.x b.y b.z |
	Vector3D V3Dcross(Vector3D a,Vector3D b){
		return Vector3D((a.y*b.z)-(a.z*b.y),(a.z*b.x)-(a.x*b.z),(a.x*b.y)-(a.y*b.x));
	}

	//angle
	double V3Dangle(Vector3D a,Vector3D b){
		return acos(V3Ddot(a,b)/(sqrt(a.magSqu()*b.magSqu())));
	}

	//vector rotation
	//v: x y z
	//rotate arround
	Vector3D V3Drotate(Vector3D v,Vector3D angle){
		double a[2][3];
		a[0][0]=sin(angle.x);
		a[0][1]=sin(angle.y);
		a[0][2]=sin(angle.z);
		a[1][0]=cos(angle.x);
		a[1][1]=cos(angle.y);
		a[1][2]=cos(angle.z);
		cos(angle.x),cos(angle.y),cos(angle.z);
		double t[3][3];
		t[0][0]=a[1][0]*a[1][1];
		t[0][1]=a[1][0]*a[0][1]*a[0][2]-a[0][0]*a[1][2];
		t[0][2]=a[1][0]*a[0][1]*a[1][2]+a[0][0]*a[0][2];
		t[1][1]=a[0][0]*a[0][1]*a[0][2]+a[1][0]*a[1][2];
		t[1][2]=a[0][0]*a[0][1]*a[1][2]-a[1][0]*a[0][2];
		t[1][0]=a[0][0]*a[1][1];
		t[2][1]=a[1][1]*a[0][2];
		t[2][2]=a[1][1]*a[1][2];
		return Vector3D(v.x*t[0][0]+v.y*t[0][1]+v.z*t[0][2],
						v.x*t[1][0]+v.y*t[1][1]+v.z*t[1][2],
						v.x*t[2][0]+v.y*t[2][1]+v.z*t[2][2]);
	}

void Vector3D::display(){
	std::cout<<"("<<this->x<<", "<<this->y<<" ,"<<this->z<<")";
}