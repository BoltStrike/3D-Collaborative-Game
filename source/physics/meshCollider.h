#ifndef MESH_COLLIDER_H
#define MESH_COLLIDER_H

#include "collider.h"
#include "internalPhysics.h"
#include <string>
#include <sstream>
#include "../generic/file_tosstream.h"
#include "../generic/program_log.h"

class MeshCollider:public Collider{
	private:
		glm::vec3* pointList;
		int numPoints;
		int* triangleList;
		int numTriangles;
		//have list of edges
		//have list of triangle areas?
	public:
		MeshCollider();
		~MeshCollider();
		MeshCollider(glm::vec3*,int, int* triangleList,int,float,glm::vec3 pos, glm::vec3 rot);
		MeshCollider(const MeshCollider &other);
		MeshCollider(std::stringstream*,float,glm::vec3 pos, glm::vec3 rot);
		
		glm::vec3* getPointList();
		int getNumPoints();
		int* getTriangleList();
		int getNumTriangles();
		
		virtual bool checkCollision(Collider*);
		//There will be functions for resolving collision, though they are not yet implimented or used
	
	//stuff for check parts of a collision
	public:
		//There may be too many functions here
		bool checkLine(glm::vec3,glm::vec3);
		bool checkLine(glm::vec3,glm::vec3,float); //cylider line
		bool checkPoint(glm::vec3);
		bool checkPoint(glm::vec3,float); //spheare
		bool secondaryEdgeCheck(Collider*);
		
	//section for collion resalutition functions
	public:
		float resolveLineVertPillVert(glm::vec3,glm::vec3,float,glm::vec3,glm::vec3,float);
	public:
		virtual float resolveVertPillVert(glm::vec3,glm::vec3,float,float);
	//internal suport functions
	public:
		inline bool areaCheck(glm::vec3,int,float);
		inline bool pointLineCheck(glm::vec3,float,int,int,int);
		inline glm::vec3 getPoint(int,int);
		inline glm::vec3 getNormal(int);
	public:
		void setPosition(glm::vec3);
		glm::vec3 getPosition();
		void setRotation(glm::vec3);
		glm::vec3 getRotation();
		
	public:
		void printTriangles();
	
};

#endif