#include "boxCollider.h"

BoxCollider::BoxCollider():Collider(ColliderType::box,sqrt(0.75f)){
	this->pointList=(glm::vec3*)malloc(8*sizeof(glm::vec3));
	pointList[0]=glm::vec3(-0.5f,-0.5f,-0.5f);
	pointList[1]=glm::vec3(-0.5f,-0.5f, 0.5f);
	pointList[2]=glm::vec3(-0.5f, 0.5f,-0.5f);
	pointList[3]=glm::vec3(-0.5f, 0.5f, 0.5f);
	pointList[4]=glm::vec3( 0.5f,-0.5f,-0.5f);
	pointList[5]=glm::vec3( 0.5f,-0.5f, 0.5f);
	pointList[6]=glm::vec3( 0.5f, 0.5f,-0.5f);
	pointList[7]=glm::vec3( 0.5f, 0.5f, 0.5f);
}
BoxCollider::~BoxCollider(){
	free(pointList);
}
//note: x,y,z are only 1/2 of the length of their respective sides
BoxCollider::BoxCollider(float x,float y,float z):Collider(ColliderType::box,glm::length(glm::vec3(x*2,y*2,z*2))){
	this->pointList=(glm::vec3*)malloc(8*sizeof(glm::vec3));
	pointList[0]=glm::vec3(-x,-y,-z);
	pointList[1]=glm::vec3(-x,-y, z);
	pointList[2]=glm::vec3(-x, y,-z);
	pointList[3]=glm::vec3(-x, y, z);
	pointList[4]=glm::vec3( x,-y,-z);
	pointList[5]=glm::vec3( x,-y, z);
	pointList[6]=glm::vec3( x, y,-z);
	pointList[7]=glm::vec3( x, y, z);
}
BoxCollider::BoxCollider(glm::vec3* pointList):Collider(ColliderType::box,glm::length(pointList[0]-pointList[7])){
	this->pointList=pointList;
}
BoxCollider::BoxCollider(const BoxCollider& other){
	this->pointList=(glm::vec3*)malloc(8*sizeof(glm::vec3));
	glm::vec3* otherPointList=other.pointList;//other.getPointList();
	for(int a=0;a<8;a++){
		this->pointList[a]=otherPointList[a];
	}
}
glm::vec3* BoxCollider::getPointList(){return this->pointList;}

bool BoxCollider::checkCollision(Collider* oCol){
	for(int i=0;i<12;i++){
		if(oCol->checkLine(this->pointList[BoxColliderLineList[i][0]],this->pointList[BoxColliderLineList[i][1]])) return true;
	}
	return oCol->secondaryEdgeCheck(this);
}
bool BoxCollider::checkLine(glm::vec3 q1,glm::vec3 q2){
	//check against each plane
	if(this->checkLineVsFace(q1,q2, 0, 1, 3, 2))return true;
	if(this->checkLineVsFace(q1,q2, 0, 4, 6, 2))return true;
	if(this->checkLineVsFace(q1,q2, 0, 1, 5, 4))return true;
	if(this->checkLineVsFace(q1,q2, 7, 3, 2, 6))return true;
	if(this->checkLineVsFace(q1,q2, 7, 3, 1, 5))return true;
	return this->checkLineVsFace(q1,q2, 7, 5, 4, 6);
}
bool BoxCollider::checkLine(glm::vec3 q1,glm::vec3 q2,float rad){ //cylider line
	//TODO
	return false;
}
bool BoxCollider::checkPoint(glm::vec3 point){
	//not sure here
	//check if it is inside?
	//do volume sum with square pirimids
	return false;
}
bool BoxCollider::checkPoint(glm::vec3 point,float rad){ //spheare
	//this can't be too bad
	//check against planes
	if(this->checkPointVsFace(point,rad, 0, 1, 3, 2))return true;
	if(this->checkPointVsFace(point,rad, 0, 4, 6, 2))return true;
	if(this->checkPointVsFace(point,rad, 0, 1, 5, 4))return true;
	if(this->checkPointVsFace(point,rad, 7, 3, 2, 6))return true;
	if(this->checkPointVsFace(point,rad, 7, 3, 1, 5))return true;
	if(this->checkPointVsFace(point,rad, 7, 5, 4, 6))return true;
	
	//check against edges
	float distance;
	for(int j=0;j<12;j++){
		//check distance
		distance=getPointToLineDistance(point,pointList[BoxColliderLineList[j][1]]-pointList[BoxColliderLineList[j][0]],pointList[BoxColliderLineList[j][0]]);
		if(distance<=rad){
			//check if on line segment
			if(between0and1(glm::length(glm::dot(pointList[BoxColliderLineList[j][1]]-pointList[BoxColliderLineList[j][0]],point-pointList[BoxColliderLineList[j][0]]))/
					glm::length(pointList[BoxColliderLineList[j][1]]-pointList[BoxColliderLineList[j][0]]))) return true;
		}
	}
	
	
	//check against points
	for(int i=0;i<8;i++){
		if(glm::length(this->pointList[i]-point)<=rad) return true;
	}
	return false;
}
void BoxCollider::applyPosRot(glm::vec3 pos,glm::vec3 rot){
	//TODO rotation
	for(int a=0;a<8;a++){
		this->pointList[a]+=pos;
	}
}
bool BoxCollider::secondaryEdgeCheck(Collider* oCol){
	//this is the same as the main check, though can leave out two edges
	for(int i=0;i<12;i++){
		if(oCol->checkLine(this->pointList[BoxColliderLineList[i][0]],this->pointList[BoxColliderLineList[i][1]])) return true;
	}
	return false;
}

bool BoxCollider::checkLineVsFace(glm::vec3 q1,glm::vec3 q2,int a,int b,int c,int d){
	glm::vec3 collisionPoint;
	glm::vec3 tempCross=glm::cross(this->pointList[a],this->pointList[b]);
	float totalArea=glm::length(tempCross);
	if(!checkLineSegmentPlane(q1,q2,tempCross/totalArea,this->pointList[a],&collisionPoint)) return false;
	//check the areas for the collision point
	float areaSum2 =glm::length(glm::cross(collisionPoint-pointList[a],pointList[b]-pointList[a]));
	areaSum2+=glm::length(glm::cross(collisionPoint-pointList[b],pointList[c]-pointList[b]));
	areaSum2+=glm::length(glm::cross(collisionPoint-pointList[c],pointList[d]-pointList[c]));
	areaSum2+=glm::length(glm::cross(collisionPoint-pointList[d],pointList[a]-pointList[d]));
	return floatsAreEqual(areaSum2,totalArea*2);	
}
bool BoxCollider::checkPointVsFace(glm::vec3 point,float rad,int a,int b,int c,int d){
	//check distance
	glm::vec3 tempCross=glm::cross(this->pointList[a],this->pointList[b]);
	float totalArea=glm::length(tempCross);
	
	float dist=glm::dot(point-pointList[a],tempCross)/totalArea;
	if(abs(dist)>rad) return false;
	//check if closest point is in the plane
	glm::vec3 collisionPoint=point-(dist*tempCross/totalArea);
	
	
	float areaSum2 =glm::length(glm::cross(collisionPoint-pointList[a],pointList[b]-pointList[a]));
	areaSum2+=glm::length(glm::cross(collisionPoint-pointList[b],pointList[c]-pointList[b]));
	areaSum2+=glm::length(glm::cross(collisionPoint-pointList[c],pointList[d]-pointList[c]));
	areaSum2+=glm::length(glm::cross(collisionPoint-pointList[d],pointList[a]-pointList[d]));
	return floatsAreEqual(areaSum2,totalArea*2);	
}
	