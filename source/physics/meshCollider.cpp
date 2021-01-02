#include "meshCollider.h"

MeshCollider::~MeshCollider(){
	free(pointList);
	free(triangleList);
}

MeshCollider::MeshCollider(glm::vec3* pointList,int numPoints, int** triangleList, int numTriangles, float rad):Collider(ColliderType::mesh,rad){
	this->pointList=pointList;
	this->numPoints=numPoints;
	this->triangleList=triangleList;
	this->numTriangles=numTriangles;
}
MeshCollider::MeshCollider(const MeshCollider &other){
	this->numPoints=other.numPoints;//getNumPoints();
	this->numTriangles=other.numTriangles;//getNumTriangles();
	this->pointList=(glm::vec3*) malloc(numPoints*sizeof(glm::vec3));
	glm::vec3* otherPoints=other.pointList;//getPointList();
	for(int a=0;a<numPoints;a++){
		this->pointList[a]=otherPoints[a];
	}
	this->triangleList=(int**) malloc(numTriangles*3*sizeof(int));
	int** otherTriangles=other.triangleList;//getTriangleList();
	for(int b=0;b<numTriangles;b++){
		this->triangleList[b][0]=otherTriangles[b][0];
		this->triangleList[b][1]=otherTriangles[b][1];
		this->triangleList[b][2]=otherTriangles[b][2];
	}
}
glm::vec3* MeshCollider::getPointList(){return this->pointList;}
int MeshCollider::getNumPoints(){return this->numPoints;}
int** MeshCollider::getTriangleList(){return this->triangleList;}
int MeshCollider::getNumTriangles(){return this->numTriangles;}

bool MeshCollider::checkCollision(Collider* oCol){
	//this ends up checking every line twice
	//maybe fix so there is a list of edges
	for(int i=0;i<numTriangles;i++){
		if(oCol->checkLine(pointList[triangleList[i][0]],pointList[triangleList[i][1]]))return true;
		if(oCol->checkLine(pointList[triangleList[i][1]],pointList[triangleList[i][2]]))return true;
		if(oCol->checkLine(pointList[triangleList[i][2]],pointList[triangleList[i][0]]))return true;
	}
	return oCol->secondaryEdgeCheck(this);
}
bool MeshCollider::checkLine(glm::vec3 q1,glm::vec3 q2){
	//check against each triangle
	glm::vec3 collisionPoint;
	glm::vec3 normal;
	float totalArea2;
	float sumArea2;
	for(int i=0;i<numTriangles;i++){
		normal=glm::cross(pointList[triangleList[i][1]]-pointList[triangleList[i][0]],pointList[triangleList[i][2]]-pointList[triangleList[i][0]]);
		totalArea2=glm::length(normal);
		if(checkLineSegmentPlane(q1,q2,normal/totalArea2,pointList[triangleList[i][0]],&collisionPoint)&&areaCheck(collisionPoint,i,totalArea2))return true;
	}
	return false;
}
bool MeshCollider::checkLine(glm::vec3 q1,glm::vec3 q2,float rad){ //cylider line
	//TODO
	return false;
}
bool MeshCollider::checkPoint(glm::vec3 point){
	//not sure here
	//check if it is inside?
	//do volume sum?
	return false;
}
bool MeshCollider::checkPoint(glm::vec3 point,float rad){ //spheare
	//this can't be too bad
	//check against planes
	float dist;
	//glm::vec3 point;
	glm::vec3 normal;
	float area2;
	for(int i=0;i<numTriangles;i++){
		//find and check distance
		normal=glm::cross(pointList[triangleList[i][1]]-pointList[triangleList[i][0]],pointList[triangleList[i][2]]-pointList[triangleList[i][0]]);
		area2=glm::length(normal);
		dist=glm::dot(point-pointList[triangleList[i][0]],normal)/area2;
		if(abs(dist)<=rad){
			//find projected point
			//check area
			if(areaCheck(point-(dist*normal/area2),i,area2)) return true;
		}
		//check against edges
		//check distance
		//check if on line segment
		if(pointLineCheck(point,rad,i,0,1))return true;
		if(pointLineCheck(point,rad,i,1,2))return true;
		if(pointLineCheck(point,rad,i,2,0))return true;
	}
	
	//check against points
	for(int b=0;b<numPoints;b++){
		if(glm::length(point-pointList[b])<=rad) return true;
	}
	return false;
}
void MeshCollider::applyPosRot(glm::vec3 pos,glm::vec3 rot){
	//TODO rotation
	for(int a=0;a<8;a++){
		this->pointList[a]+=pos;
	}
}
bool MeshCollider::secondaryEdgeCheck(Collider* oCol){
	//this is the same as the main check, though can leave out one edge per triangle
	//this sometimes ends up checking lines twice
	for(int i=0;i<numTriangles;i++){
		if(oCol->checkLine(pointList[triangleList[i][0]],pointList[triangleList[i][1]]))return true;
		if(oCol->checkLine(pointList[triangleList[i][1]],pointList[triangleList[i][2]]))return true;
	}
	return false;
}
inline bool MeshCollider::areaCheck(glm::vec3 point,int tri,float area2){
	float areaSum2 =glm::length(glm::cross(point-pointList[triangleList[tri][0]],pointList[triangleList[tri][1]]-pointList[triangleList[tri][0]]));
	areaSum2+=glm::length(glm::cross(point-pointList[triangleList[tri][1]],pointList[triangleList[tri][2]]-pointList[triangleList[tri][1]]));
	areaSum2+=glm::length(glm::cross(point-pointList[triangleList[tri][2]],pointList[triangleList[tri][0]]-pointList[triangleList[tri][2]]));
	return floatsAreEqual(area2,areaSum2);
}
inline bool MeshCollider::pointLineCheck(glm::vec3 point,float rad,int tri,int a,int b){
	float dist=getPointToLineDistance(point,pointList[triangleList[tri][a]],pointList[triangleList[tri][b]]);
	if(dist<=rad){
		if(between0and1(glm::length(glm::dot(pointList[triangleList[tri][b]]-pointList[triangleList[tri][a]],point-pointList[triangleList[tri][a]]))/
				glm::length(pointList[triangleList[tri][b]]-pointList[triangleList[tri][a]])))return true;
	}
	return false;
}
	