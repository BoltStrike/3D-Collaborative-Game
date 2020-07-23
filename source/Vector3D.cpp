//libray for vertor stuff
#include <math.h>
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

	//returns the magnatude of the vector
	double Vector3D::mag(void){
		return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	}

	//returns the magnatude squared of the vector
	//this is computaionaly easer than mag(), but does the same job
	double Vector3D::magSqu(void){
		return pow(x,2)+pow(y,2)+pow(z,2);
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
	
	///dot product
	static double V3Ddot(Vector3D a,Vector3D b){
		return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
	}
	
	//cross prduct
	//|  X   Y   Z  |
	//| a.x a.y a.z |
	//| b.x b.y b.z |
	static Vector3D V3Dcross(Vector3D a,Vector3D b){
		return Vector3D((a.y*b.z)-(a.z*b.y),(a.z*b.x)-(a.x*b.z),(a.x*b.y)-(a.y*b.x));
	}
	
	//angle
	static double V3Dangle(Vector3D a,Vector3D b){
		return acos(V3Ddot(a,b)/(sqrt(a.magSqu()*b.magSqu())));
	}



