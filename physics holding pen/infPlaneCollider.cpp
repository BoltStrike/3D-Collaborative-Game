#include "infPlaneCollider.h"

InfPlaneCollider::InfPlaneCollider():Collider(ColliderType::infPlane,INFINITY){
	this->point=glm::vec3(0.0f,0.0f,0.0f);
	this->normal=glm::vec3(0.0f,1.0f,0.0f);
}
InfPlaneCollider::~InfPlaneCollider(){
	
}
InfPlaneCollider::InfPlaneCollider(glm::vec3 p,glm::vec3 n):Collider(ColliderType::infPlane,INFINITY){
	this->point=p;
	this->normal=n;
}
InfPlaneCollider::InfPlaneCollider(std::stringstream* stream,float rad):Collider(ColliderType::infPlane,rad){
	float x,y,z;
	(*stream)>>x>>y>>z;
	this->point=glm::vec3(x,y,z);
	(*stream)>>x>>y>>z;
	this->normal=glm::vec3(x,y,z);
}
InfPlaneCollider::InfPlaneCollider(const InfPlaneCollider &old){
	point=old.point;
	normal=old.normal;
}

/*bool InfPlaneCollider::checkCollision(glm::vec3 pos,glm::vec3 rot,Collider* otherCol,glm::vec3 otherPos,glm::vec3 otherRot){
	//flip the direction unless the other collider is also a infinate plane
	if(otherCol->getType()!=ColliderType::infPlane) return otherCol->checkCollision(otherPos,otherRot,this,pos,rot);
	//handle the inf plane
	InfPlaneCollider* temp=((InfPlaneCollider*)otherCol);
	InfPlaneCollider oCol=*temp;
	oCol.applyPosRot(otherPos,otherRot);
	glm::vec3 oldPoint=this->point;
	glm::vec3 oldNormal=this->normal;
	this->applyPosRot(pos,rot);
	
	//restore old values
	this->point=oldPoint;
	this->normal=oldNormal;
	return resualt;
}*/

bool InfPlaneCollider::checkCollision(Collider* otherCol){
	if(otherCol->getType()!=ColliderType::infPlane) return otherCol->checkCollision(this);
	InfPlaneCollider* oCol=(InfPlaneCollider*) otherCol;
	/* Case for non collision
	 * Normals equal and dist between point and plane is non zero
	*/
	if(this->normal!=oCol->getNormal()) return true;
	else if((glm::length(glm::dot(this->point-oCol->getPoint(),this->normal))/glm::length(this->normal))==0)return true;
	else return false;
}

glm::vec3 InfPlaneCollider::getPoint(){
	return this->point;
}
glm::vec3 InfPlaneCollider::getNormal(){
	return this->normal;
}

bool InfPlaneCollider::checkLine(glm::vec3 q1,glm::vec3 q2){
	/*glm::vec3 lineVect=q2-q1;
	if(ofFloatIsEqual(glm::dot(lineVect,this->normal),0.0f)){
		//line is paralle to the plane
		//check if point is on the plane
		return this->checkPoint(q1);
	}*/
	//see if line intersects the plane
	//check if the points are on opisit sides of the plane
	return (glm::dot(this->point-q1,this->normal)*glm::dot(this->point-q1,this->normal))<=0;
}
bool InfPlaneCollider::checkLine(glm::vec3 q1,glm::vec3 q2,float r){ //cylider line
	//TODO
	return false;
}
bool InfPlaneCollider::checkPoint(glm::vec3 point){
	return floatsAreEqual((glm::length(glm::dot(this->point-point,this->normal))/glm::length(this->normal)),0.0f);
}
bool InfPlaneCollider::checkPoint(glm::vec3 point,float rad){ //spheare
	return (glm::length(glm::dot(this->point-point,this->normal))/glm::length(this->normal))<=rad;
}
bool InfPlaneCollider::secondaryEdgeCheck(Collider* oCol){
	return false;
}
void InfPlaneCollider::applyPosRot(glm::vec3 pos,glm::vec3 rot){
	this->point+=pos;
	//TODO apply rotation to normal and pos
}