#include "collider.h"
Collider::Collider(){
	type=ColliderTypes.none;
}
Collider::Collider(ColliderTypes ct){
	type=ct;
}
Collider::ColliderType getColliderType(){
	return type;
}
static bool Collider::checkCollision(BoxCollider* a,Vector3D posA,Vector3D angA,BoxCollider* b,Vector3D posB,Vector3D angB){
	//checking colision between two boxes
	//check collision between all the faces
	Vector3D* boxA=new Vector3D[3];
	for(int i=0;i<3;i++){
		boxA[i]=V3Drotate(a.getNormals()[i],angA);
	}
	Vector3D* boxB=new Vector3D[3];
	for(int i=0;i<3;i++){
		boxB[i]=V3Drotate(b.getNormals()[i],angB);
	}
	//check the edges of box A against the Sides of Box B
	Collider.lineVsBox(boxA[0],posA+boxA[0]+boxA[1]+boxA[2],posA-boxA[0]+boxA[1]+boxA[2],boxB,posB);
	Collider.lineVsBox(boxA[0],posA+boxA[0]-boxA[1]+boxA[2],posA-boxA[0]-boxA[1]+boxA[2],boxB,posB);
	Collider.lineVsBox(boxA[0],posA+boxA[0]+boxA[1]-boxA[2],posA-boxA[0]+boxA[1]-boxA[2],boxB,posB);
	Collider.lineVsBox(boxA[0],posA+boxA[0]-boxA[1]-boxA[2],posA-boxA[0]-boxA[1]-boxA[2],boxB,posB);
	
	Collider.lineVsBox(boxA[1],posA+boxA[1]+boxA[0]+boxA[2],posA-boxA[1]+boxA[0]+boxA[2],boxB,posB);
	Collider.lineVsBox(boxA[1],posA+boxA[1]-boxA[0]+boxA[2],posA-boxA[1]-boxA[0]+boxA[2],boxB,posB);
	Collider.lineVsBox(boxA[1],posA+boxA[1]+boxA[0]-boxA[2],posA-boxA[1]+boxA[0]-boxA[2],boxB,posB);
	Collider.lineVsBox(boxA[1],posA+boxA[1]-boxA[0]-boxA[2],posA-boxA[1]-boxA[0]-boxA[2],boxB,posB);
	
	Collider.lineVsBox(boxA[2],posA+boxA[2]+boxA[0]+boxA[1],posA-boxA[2]+boxA[0]+boxA[1],boxB,posB);
	Collider.lineVsBox(boxA[2],posA+boxA[2]-boxA[0]+boxA[1],posA-boxA[2]-boxA[0]+boxA[1],boxB,posB);
	Collider.lineVsBox(boxA[2],posA+boxA[2]+boxA[0]-boxA[1],posA-boxA[2]+boxA[0]-boxA[1],boxB,posB);
	Collider.lineVsBox(boxA[2],posA+boxA[2]-boxA[0]-boxA[1],posA-boxA[2]-boxA[0]-boxA[1],boxB,posB);
	
	//check the edges of box B against the Sides of Box A
	Collider.lineVsBox(boxA[0],posA+boxA[0]+boxA[1]+boxA[2],posA-boxA[0]+boxA[1]+boxA[2],boxA,posA);
	Collider.lineVsBox(boxA[0],posA+boxA[0]-boxA[1]+boxA[2],posA-boxA[0]-boxA[1]+boxA[2],boxA,posA);
	Collider.lineVsBox(boxA[0],posA+boxA[0]+boxA[1]-boxA[2],posA-boxA[0]+boxA[1]-boxA[2],boxA,posA);
	Collider.lineVsBox(boxA[0],posA+boxA[0]-boxA[1]-boxA[2],posA-boxA[0]-boxA[1]-boxA[2],boxA,posA);
	
	Collider.lineVsBox(boxA[1],posA+boxA[1]+boxA[0]+boxA[2],posA-boxA[1]+boxA[0]+boxA[2],boxA,posA);
	Collider.lineVsBox(boxA[1],posA+boxA[1]-boxA[0]+boxA[2],posA-boxA[1]-boxA[0]+boxA[2],boxA,posA);
	Collider.lineVsBox(boxA[1],posA+boxA[1]+boxA[0]-boxA[2],posA-boxA[1]+boxA[0]-boxA[2],boxA,posA);
	Collider.lineVsBox(boxA[1],posA+boxA[1]-boxA[0]-boxA[2],posA-boxA[1]-boxA[0]-boxA[2],boxA,posA);
	
	Collider.lineVsBox(boxA[2],posA+boxA[2]+boxA[0]+boxA[1],posA-boxA[2]+boxA[0]+boxA[1],boxA,posA);
	Collider.lineVsBox(boxA[2],posA+boxA[2]-boxA[0]+boxA[1],posA-boxA[2]-boxA[0]+boxA[1],boxA,posA);
	Collider.lineVsBox(boxA[2],posA+boxA[2]+boxA[0]-boxA[1],posA-boxA[2]+boxA[0]-boxA[1],boxA,posA);
	Collider.lineVsBox(boxA[2],posA+boxA[2]-boxA[0]-boxA[1],posA-boxA[2]-boxA[0]-boxA[1],boxA,posA);
	
	//check if box A or B is inside eachother
	//leaving out for now, might cause missed collisions with high speed collisions with low physics update rate
	
}

static bool Collider::lineVsBox(Vector3D line,Vector3D pointA,Vector3D pointB,Vector3D* normals,Vector3D posB){
	double temp;
	double maxT=(pointA.x-pointB.x)/line.x;
	for(int i=0;i<=3;i++){
		temp=V3Ddot((normals[i]+posB)-pointA,normals[i])/V3Ddot(normals[i],line);
		if((maxT<0)?(temp>=maxT && temp<=0):(temp>=0 && temp<=maxT)) return true;
	}
	for(int i=0;i<=3;i++){
		temp=V3Ddot((-normals[i]+posB)-pointA,-normals[i])/V3Ddot(-normals[i],line);
		if((maxT<0)?(temp>=maxT && temp<=0):(temp>=0 && temp<=maxT)) return true;
	}
}