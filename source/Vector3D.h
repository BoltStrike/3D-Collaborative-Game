#ifndef Vector3D_h
#define Vector3D_h
class Vector3D{
	public:
	double x;
	double y;
	double z;
	Vector3D(double x,double y,double z);
	Vector3D(double* val);
	Vector3D();
	//returns the magnatude of the vector
	double mag(void);

	//returns the magnatude squared of the vector
	//this is computaionaly easer than mag(), but does the same job
	double magSqu(void);

	//scales each value by a certian amount
	Vector3D scale(double ammount);

	//returns a unit vector in the direction of it's self
	Vector3D unit();

	//adds a value to it's self
	Vector3D add(Vector3D ammount);
	
	Vector3D opperator+(const &Vector3D);
	Vector3D opperator-(const &Vector3D);
	Vector3D opperator-();
	
	bool isZero();
	
};
	//dot product
	static double V3Ddot(Vector3D a,Vector3D b);

	//cross prduct
	//|  X   Y   Z  |
	//| a.x a.y a.z |
	//| b.x b.y b.z |
	static Vector3D V3Dcross(Vector3D a,Vector3D b);

	//angle
	static double V3Dangle(Vector3D a,Vector3D b);

	static Vector3D V3Drotate(Vector3D v,Vector3D angle);

#endif
