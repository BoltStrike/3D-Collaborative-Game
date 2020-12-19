#include "boxCollider.h"

BoxCollider::BoxCollider():Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=new Vector3D(1.0,0.0,0.0);
	normals[1]=new Vector3D(0.0,1.0,0.0);
	normals[2]=new Vector3D(0.0,0.0,1.0);
}
BoxCollider::BoxCollider(double w,double l,double h):Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=new Vector3D(w,0.0,0.0);
	normals[1]=new Vector3D(0.0,l,0.0);
	normals[2]=new Vector3D(0.0,0.0,h);
}
BoxCollider::BoxCollider(Vector3D* a,Vector3D* b,Vector3D* c):Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=a;
	normals[1]=b;
	normals[2]=c;
}
BoxCollider::~BoxCollider(){
}
Vector3D** BoxCollider::getNormals(){
	return normals;
}
int BoxCollider::checkCollision(Vector3D* posA,Vector3D* angA,Collider* b,Vector3D* posB,Vector3D* angB){
	switch(b->getColliderType()){
		case ColliderType::box:
			return checkCollision(this,posA,angA,(BoxCollider*)b,posB,angB);
		default:
			return 0;
		
	}
}

int BoxCollider::checkCollision(BoxCollider* a,Vector3D* posA,Vector3D* angA,BoxCollider* b,Vector3D* posB,Vector3D* angB){
	//checking colision between two boxes
	//check collision between all the faces
	Vector3D* boxA=new Vector3D[3];
	for(int i=0;i<3;i++){
		boxA[i]=V3Drotate(*a->getNormals()[i],*angA);
	}
	Vector3D* boxB=new Vector3D[3];
	for(int i=0;i<3;i++){
		boxB[i]=V3Drotate(*b->getNormals()[i],*angB);
	}
	//check the edges of box A against the Sides of Box B
	if(lineVsBox(boxA[0],*posA+boxA[0]+boxA[1]+boxA[2],*posA-boxA[0]+boxA[1]+boxA[2],boxB,posB))return 1;
	if(lineVsBox(boxA[0],*posA+boxA[0]-boxA[1]+boxA[2],*posA-boxA[0]-boxA[1]+boxA[2],boxB,posB))return 2;
	if(lineVsBox(boxA[0],*posA+boxA[0]+boxA[1]-boxA[2],*posA-boxA[0]+boxA[1]-boxA[2],boxB,posB))return 3;
	if(lineVsBox(boxA[0],*posA+boxA[0]-boxA[1]-boxA[2],*posA-boxA[0]-boxA[1]-boxA[2],boxB,posB))return 4;
	
	if(lineVsBox(boxA[1],*posA+boxA[1]+boxA[0]+boxA[2],*posA-boxA[1]+boxA[0]+boxA[2],boxB,posB))return 5;
	if(lineVsBox(boxA[1],*posA+boxA[1]-boxA[0]+boxA[2],*posA-boxA[1]-boxA[0]+boxA[2],boxB,posB))return 6;
	if(lineVsBox(boxA[1],*posA+boxA[1]+boxA[0]-boxA[2],*posA-boxA[1]+boxA[0]-boxA[2],boxB,posB))return 7;
	if(lineVsBox(boxA[1],*posA+boxA[1]-boxA[0]-boxA[2],*posA-boxA[1]-boxA[0]-boxA[2],boxB,posB))return 8;
	
	if(lineVsBox(boxA[2],*posA+boxA[2]+boxA[0]+boxA[1],*posA-boxA[2]+boxA[0]+boxA[1],boxB,posB))return 9;
	if(lineVsBox(boxA[2],*posA+boxA[2]-boxA[0]+boxA[1],*posA-boxA[2]-boxA[0]+boxA[1],boxB,posB))return 10;
	if(lineVsBox(boxA[2],*posA+boxA[2]+boxA[0]-boxA[1],*posA-boxA[2]+boxA[0]-boxA[1],boxB,posB))return 11;
	if(lineVsBox(boxA[2],*posA+boxA[2]-boxA[0]-boxA[1],*posA-boxA[2]-boxA[0]-boxA[1],boxB,posB))return 12;
	
	//check the edges of box B against the Sides of Box A
	if(lineVsBox(boxA[0],*posA+boxA[0]+boxA[1]+boxA[2],*posA-boxA[0]+boxA[1]+boxA[2],boxA,posA))return 13;
	if(lineVsBox(boxA[0],*posA+boxA[0]-boxA[1]+boxA[2],*posA-boxA[0]-boxA[1]+boxA[2],boxA,posA))return 14;
	if(lineVsBox(boxA[0],*posA+boxA[0]+boxA[1]-boxA[2],*posA-boxA[0]+boxA[1]-boxA[2],boxA,posA))return 15;
	if(lineVsBox(boxA[0],*posA+boxA[0]-boxA[1]-boxA[2],*posA-boxA[0]-boxA[1]-boxA[2],boxA,posA))return 16;
	
	if(lineVsBox(boxA[1],*posA+boxA[1]+boxA[0]+boxA[2],*posA-boxA[1]+boxA[0]+boxA[2],boxA,posA))return 17;
	if(lineVsBox(boxA[1],*posA+boxA[1]-boxA[0]+boxA[2],*posA-boxA[1]-boxA[0]+boxA[2],boxA,posA))return 18;
	if(lineVsBox(boxA[1],*posA+boxA[1]+boxA[0]-boxA[2],*posA-boxA[1]+boxA[0]-boxA[2],boxA,posA))return 19;
	if(lineVsBox(boxA[1],*posA+boxA[1]-boxA[0]-boxA[2],*posA-boxA[1]-boxA[0]-boxA[2],boxA,posA))return 20;
	
	if(lineVsBox(boxA[2],*posA+boxA[2]+boxA[0]+boxA[1],*posA-boxA[2]+boxA[0]+boxA[1],boxA,posA))return 21;
	if(lineVsBox(boxA[2],*posA+boxA[2]-boxA[0]+boxA[1],*posA-boxA[2]-boxA[0]+boxA[1],boxA,posA))return 22;
	if(lineVsBox(boxA[2],*posA+boxA[2]+boxA[0]-boxA[1],*posA-boxA[2]+boxA[0]-boxA[1],boxA,posA))return 23;
	if(lineVsBox(boxA[2],*posA+boxA[2]-boxA[0]-boxA[1],*posA-boxA[2]-boxA[0]-boxA[1],boxA,posA))return 24;
	
	//check if box A or B is inside eachother
	//leaving out for now, might cause missed collisions with high speed collisions with low physics update rate
	return 0;
}

static bool lineVsBox(Vector3D line,Vector3D pointA,Vector3D pointB,Vector3D* normals,Vector3D* posB){
	double temp;
	double maxT=(pointA.x-pointB.x)/line.x;
	for(int i=0;i<=3;i++){
		temp=V3Ddot((normals[i]+(*posB))-pointA,normals[i])/V3Ddot(normals[i],line);
		if((maxT<0)?(temp>=maxT && temp<=0):(temp>=0 && temp<=maxT)) return true;
	}
	for(int i=0;i<=3;i++){
		temp=V3Ddot((-normals[i]+(*posB))-pointA,-normals[i])/V3Ddot(-normals[i],line);
		if((maxT<0)?(temp>=maxT && temp<=0):(temp>=0 && temp<=maxT)) return true;
	}
	return false;
}
