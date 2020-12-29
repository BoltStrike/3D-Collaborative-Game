#ifndef MESH_COLLIDER
#define MESH_COLLIDER

#include "Vector3D.h"
#include "globalPhysics.h"
#include "collider.h"
#include "triangle.h"
#include "resolvedData.h"
#include "timeAndId.h"

class MeshCollider:public Collider{
	private:
	int numPoints;
	int numTriangles;
	Vector3D* points;
	Triangle* triangles;
	public:
	MeshCollider();
	MeshCollider(int, Vector3D*, Vector3D*, int, int*);
	MeshCollider(const MeshCollider &obj);
	~MeshCollider();
	MeshCollider(int);
	
	public:
	int getNumPoints() const;
	int getNumTriangles() const;
	Vector3D* getPoints() const;
	Triangle* getTriangles() const;
	
	public:
	void rotateMove(Vector3D* rot, Vector3D* pos);
	virtual int checkCollision(Vector3D*,Vector3D*,Collider*,Vector3D*,Vector3D*);
	virtual ResolvedData fixCollision(Vector3D*,Vector3D*,Vector3D*,Collider*,Vector3D*,Vector3D*);
	int checkLine(Vector3D line,Vector3D* pointA,Vector3D* pointB);
	int checkMesh(MeshCollider*);
	Vector3D getTrianglePoint(int,int);
	
};

#endif