#include "boxCollider.h"
#include <iostream>

BoxCollider::BoxCollider():Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=new Vector3D(1.0,0.0,0.0);
	normals[1]=new Vector3D(0.0,1.0,0.0);
	normals[2]=new Vector3D(0.0,0.0,1.0);
}
BoxCollider::BoxCollider(double w,double l,double h):Collider(ColliderType::box){
	//Collider(ColliderType.box);
	normals[0]=new Vector3D(w/2,0.0,0.0);
	normals[1]=new Vector3D(0.0,l/2,0.0);
	normals[2]=new Vector3D(0.0,0.0,h/2);
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
	std::cout<<"Box collision Check"<<std::endl;
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
	std::cout<<"posA: ";
	posA->display();
	std::cout<<std::endl;
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
	if(lineVsBox(boxB[0],*posB+boxB[0]+boxB[1]+boxB[2],*posB-boxB[0]+boxB[1]+boxB[2],boxA,posA))return 13;
	if(lineVsBox(boxB[0],*posB+boxB[0]-boxB[1]+boxB[2],*posB-boxB[0]-boxB[1]+boxB[2],boxA,posA))return 14;
	if(lineVsBox(boxB[0],*posB+boxB[0]+boxB[1]-boxB[2],*posB-boxB[0]+boxB[1]-boxB[2],boxA,posA))return 15;
	if(lineVsBox(boxB[0],*posB+boxB[0]-boxB[1]-boxB[2],*posB-boxB[0]-boxB[1]-boxB[2],boxA,posA))return 16;
	
	if(lineVsBox(boxB[1],*posB+boxB[1]+boxB[0]+boxB[2],*posB-boxB[1]+boxB[0]+boxB[2],boxA,posA))return 17;
	if(lineVsBox(boxB[1],*posB+boxB[1]-boxB[0]+boxB[2],*posB-boxB[1]-boxB[0]+boxB[2],boxA,posA))return 18;
	if(lineVsBox(boxB[1],*posB+boxB[1]+boxB[0]-boxB[2],*posB-boxB[1]+boxB[0]-boxB[2],boxA,posA))return 19;
	if(lineVsBox(boxB[1],*posB+boxB[1]-boxB[0]-boxB[2],*posB-boxB[1]-boxB[0]-boxB[2],boxA,posA))return 20;
	
	if(lineVsBox(boxB[2],*posB+boxB[2]+boxB[0]+boxB[1],*posB-boxB[2]+boxB[0]+boxB[1],boxA,posA))return 21;
	if(lineVsBox(boxB[2],*posB+boxB[2]-boxB[0]+boxB[1],*posB-boxB[2]-boxB[0]+boxB[1],boxA,posA))return 22;
	if(lineVsBox(boxB[2],*posB+boxB[2]+boxB[0]-boxB[1],*posB-boxB[2]+boxB[0]-boxB[1],boxA,posA))return 23;
	if(lineVsBox(boxB[2],*posB+boxB[2]-boxB[0]-boxB[1],*posB-boxB[2]-boxB[0]-boxB[1],boxA,posA))return 24;
	
	//check if box A or B is inside eachother
	//leaving out for now, might cause missed collisions with high speed collisions with low physics update rate
	return 0;
}
static bool lineVsBox(Vector3D line,Vector3D pointA,Vector3D pointB,Vector3D* normals,Vector3D* posB){
	/*std::cout<<"lineVsBox:"<<std::endl<<"\t\tline: ";
	line.display();
	std::cout<<std::endl<<"\t\tpointA: ";
	pointA.display();
	std::cout<<std::endl<<"\t\tpointB: ";
	pointB.display();
	std::cout<<std::endl<<"\t\tnormals[0]: ";
	normals[0].display();
	std::cout<<std::endl<<"\t\tnormals[1]: ";
	normals[1].display();
	std::cout<<std::endl<<"\t\tnormals[2]: ";
	normals[2].display();
	std::cout<<std::endl<<"\t\tposB: ";
	posB->display();
	std::cout<<std::endl<<std::endl;*/
	double temp;
	double sideArea;
	double interiorArea;
	Vector3D point;
	Vector3D diffrence=pointB-pointA;
	double maxT=(line.x==0)?((line.y==0)?(diffrence.z/line.z):(diffrence.y/line.y)):(diffrence.x/line.x);
	//std::cout<<"\t\tmaxT="<<maxT<<std::endl;
	for(int i=0;i<3;i++){
		temp=V3Ddot((normals[i]+(*posB))-pointA,normals[i])/V3Ddot(normals[i],line);
		//std::cout<<"\t\t pos normal["<<i<<"], temp="<<temp<<std::endl;
		if((maxT<0)?(temp>=maxT && temp<=0):(temp>=0 && temp<=maxT)){
			sideArea=V3Dcross(normals[(i+1)%3],normals[(i+2)%3]).mag()*4;
			point=pointA+line.scale(temp);
			interiorArea=V3Dcross(-normals[(i+1)%3],normals[(i+1)%3]+normals[(i+2)%3]-point+(*posB)+normals[i]).mag();
			interiorArea+=V3Dcross(-normals[(i+2)%3],normals[(i+1)%3]+normals[(i+2)%3]-point+(*posB)+normals[i]).mag();
			interiorArea+=V3Dcross(-normals[(i+1)%3],-normals[(i+1)%3]-normals[(i+2)%3]-point+(*posB)+normals[i]).mag();
			interiorArea+=V3Dcross(normals[(i+2)%3],-normals[(i+1)%3]+normals[(i+2)%3]-point+(*posB)+normals[i]).mag();
			if(interiorArea==sideArea) return true;
		}
	}
	for(int i=0;i<3;i++){
		temp=V3Ddot((-normals[i]+(*posB))-pointA,-normals[i])/V3Ddot(-normals[i],line);
		//std::cout<<"\t\t neg normal["<<i<<"], temp="<<temp<<std::endl;
		if((maxT<0)?(temp>=maxT && temp<=0):(temp>=0 && temp<=maxT)){
			sideArea=V3Dcross(normals[(i+1)%3],normals[(i+2)%3]).mag()*4;
			point=pointA+line.scale(temp);
			interiorArea=V3Dcross(-normals[(i+1)%3],normals[(i+1)%3]+normals[(i+2)%3]-point+(*posB)-normals[i]).mag();
			interiorArea+=V3Dcross(-normals[(i+2)%3],normals[(i+1)%3]+normals[(i+2)%3]-point+(*posB)-normals[i]).mag();
			interiorArea+=V3Dcross(-normals[(i+1)%3],-normals[(i+1)%3]-normals[(i+2)%3]-point+(*posB)-normals[i]).mag();
			interiorArea+=V3Dcross(normals[(i+2)%3],-normals[(i+1)%3]+normals[(i+2)%3]-point+(*posB)-normals[i]).mag();
			if(interiorArea==sideArea) return true;
		}
	}
	return false;
}

ResolvedData BoxCollider::fixCollision(Vector3D pointA,Vector3D pointB,Vector3D line, Vector3D* velocity, Vector3D* normals, Vector3D* posB){
	ResolvedData output=ResolvedData();
	Vector3D movementPlaneNormal=V3Dcross(line,*velocity);
	if(movementPlaneNormal.isZero()){
		//line and velocity are pointing in the same direction
		//TODO later
	}
	double shortestTime=INFINITY;
	double tempTime;
	Vector3D intersectPoint;
	Vector3D intersectLine;
	for(int i=0;i<3;i++){
		if(V3DsameNormal(movementPlaneNormal,normals[i])){
			//The planes are parallel and a collision is happening so the line must lie on plane
			return output;
		}else{
			//this is probibly genaric case
			intersectPoint=Collider::collideTwoPlanes(movementPlaneNormal,pointA,normals[i],normals[i]+(*posB));
			intersectLine=V3Dcross(normals[i],movementPlaneNormal);
			//check if the intersection line intersects the side
			
			//find distance between the the end points and the intersect line in the direction of velocity
			if(line.x!=0){
				tempTime=(intersectPoint.x-pointA.x);
			}else if(line.y!=0){
				
			}
		}
	}
	return output;
}
ResolvedData BoxCollider::fixCollision(BoxCollider* a,Vector3D* posA,Vector3D* angA,Vector3D* velA,BoxCollider*otherCollider,Vector3D* posB,Vector3D* angB){
	Vector3D* boxA=new Vector3D[3];
	for(int i=0;i<3;i++){
		boxA[i]=V3Drotate(*a->getNormals()[i],*angA);
	}
	Vector3D* boxB=new Vector3D[3];
	for(int i=0;i<3;i++){
		boxB[i]=V3Drotate(*otherCollider->getNormals()[i],*angB);
	}
	return ResolvedData();
}
ResolvedData BoxCollider::fixCollision(Vector3D* posA,Vector3D* angA,Vector3D* velA,Collider* otherCollider,Vector3D* posB,Vector3D* rotB){
	//figure out how to resolve the collision
	switch(otherCollider->getColliderType()){
		case ColliderType::box:
			return fixCollision(this,posA,angA,velA,(BoxCollider*)otherCollider,posB,rotB);
		default:
			return ResolvedData();
		
	}
	return ResolvedData();
}
