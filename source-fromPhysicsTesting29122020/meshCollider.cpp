#include "meshCollider.h"

MeshCollider::MeshCollider(int numPoints, Vector3D* points, Vector3D* normals, int numTriangles, int* triangles):Collider(ColliderType::mesh){
	this->numPoints=numPoints;
	this->numTriangles=numTriangles;
	this->points=points;
	this->triangles=(Triangle*)malloc(sizeof(Triangle)*numTriangles);
	int maxTriangleIndex=numTriangles<<2;
	for(int i=0;i<maxTriangleIndex;i+=4){
		this->triangles[i]=Triangle(triangles[i],triangles[i+1],triangles[i+2],normals[triangles[i+3]]);
	}
	
}
MeshCollider::MeshCollider():Collider(ColliderType::mesh){
	//make basic triangular pirimid
	this->numPoints=4;
	this->numTriangles=4;
	this->points=(Vector3D*)malloc(sizeof(Vector3D)*4);
	this->triangles=(Triangle*)malloc(sizeof(Triangle)*4);
	points[0]=Vector3D(1,0.5,0);
	points[1]=Vector3D(-0.5,0.5,0.5);
	points[2]=Vector3D(-0.5,0.5,-0.5);
	points[3]=Vector3D(0,-0.5,0);
	this->triangles[0]=Triangle(0,1,2,points);
	this->triangles[0]=Triangle(3,0,2,points);
	this->triangles[0]=Triangle(3,1,0,points);
	this->triangles[0]=Triangle(3,2,1,points);
}
MeshCollider::MeshCollider(const MeshCollider &obj){
	this->numPoints=obj.getNumPoints();
	this->numTriangles=obj.getNumTriangles();
	this->points=(Vector3D*)malloc(sizeof(Vector3D)*numPoints);
	this->triangles=(Triangle*)malloc(sizeof(Triangle)*numTriangles);
	//coppy the points
	Vector3D* temp=obj.getPoints();
	for(int a=0;a<numPoints;a++){
		this->points[a]=temp[a];
	}
	//coppy the triangles
	Triangle* tri=obj.getTriangles();
	for(int b=0;b<numTriangles;b++){
		this->triangles[b]=tri[b];
	}
}
MeshCollider::~MeshCollider(){
	delete points;
	delete triangles;
}
//generatates a cube
MeshCollider::MeshCollider(int size){
	this->numPoints=8;
	this->numTriangles=12;
	this->points=new Vector3D[8];
	this->triangles=new Triangle[12];
	this->points[0]=Vector3D(-size,-size,-size);
	this->points[1]=Vector3D(-size,-size,size);
	this->points[2]=Vector3D(-size,size,-size);
	this->points[3]=Vector3D(-size,size,size);
	this->points[4]=Vector3D(size,-size,-size);
	this->points[5]=Vector3D(size,-size,size);
	this->points[6]=Vector3D(size,size,-size);
	this->points[7]=Vector3D(size,size,size);
	this->triangles[0]=Triangle(0,1,2,Vector3D(-1,0,0));
	this->triangles[1]=Triangle(3,1,2,Vector3D(-1,0,0));
	this->triangles[2]=Triangle(0,2,4,Vector3D(0,0,-1));
	this->triangles[3]=Triangle(4,2,6,Vector3D(0,0,-1));
	this->triangles[4]=Triangle(4,5,7,Vector3D(1,0,0));
	this->triangles[5]=Triangle(4,6,7,Vector3D(1,0,0));
	this->triangles[6]=Triangle(5,1,7,Vector3D(0,0,1));
	this->triangles[7]=Triangle(7,1,3,Vector3D(0,0,1));
	this->triangles[8]=Triangle(1,0,4,Vector3D(0,-1,0));
	this->triangles[9]=Triangle(1,5,4,Vector3D(0,-1,0));
	this->triangles[10]=Triangle(2,3,6,Vector3D(0,1,0));
	this->triangles[11]=Triangle(7,3,6,Vector3D(0,1,0));
}

int MeshCollider::getNumPoints() const{return numPoints;}
int MeshCollider::getNumTriangles() const{return numTriangles;}
Vector3D* MeshCollider::getPoints() const{return points;}
Triangle* MeshCollider::getTriangles() const{return triangles;}



void MeshCollider::rotateMove(Vector3D* rot, Vector3D* pos){
	//rotate and move all the points
	for(int a=0;a<numPoints;a++){
		points[a]=V3Drotate(points[a],*rot)+(*pos);
	}
	//rotate all the normals in the triangles
	for(int b=0;b<numTriangles;b++){
		triangles[b].rotateNormal(rot);
	}
}
int MeshCollider::checkCollision(Vector3D* posA,Vector3D* rotA,Collider* b,Vector3D* posB,Vector3D* rotB){
	//check spheres of infuence
	//TODO
	int temp;
	if(b->getColliderType()==ColliderType::mesh){
		MeshCollider copyA=*this;
		MeshCollider copyB=*((MeshCollider*) b);
		copyA.rotateMove(rotA,posA);
		copyB.rotateMove(rotB,posB);
		temp=copyA.checkMesh(&copyB);
		if(temp!=0) return temp;
		return copyB.checkMesh(&copyA);
	}else{
		return 0;
	}
	
}
int MeshCollider::checkMesh(MeshCollider* other){
	int temp;
	for(int i=0;i<numTriangles;i++){
		if((temp=other->checkLine(points[triangles[i].pointA]-points[triangles[i].pointB],&points[triangles[i].pointA],&points[triangles[i].pointB]))!=0)return temp;
		if((temp=other->checkLine(points[triangles[i].pointA]-points[triangles[i].pointC],&points[triangles[i].pointA],&points[triangles[i].pointC]))!=0)return temp;
		if((temp=other->checkLine(points[triangles[i].pointB]-points[triangles[i].pointC],&points[triangles[i].pointB],&points[triangles[i].pointC]))!=0)return temp;
	}
	return 0;
}
int MeshCollider::checkLine(Vector3D line,Vector3D* pointA,Vector3D* pointB){
	for(int i=0;i<numTriangles;i++){
		if(triangles[i].checkAgainstLine(line,pointA,pointB,points))return i+1;
	}
	return 0;
}
ResolvedData MeshCollider::fixCollision(Vector3D*,Vector3D*,Vector3D*,Collider*,Vector3D*,Vector3D*){
	return ResolvedData();
}
Vector3D MeshCollider::getTrianglePoint(int tri,int point){
	return this->points[this->triangles[tri].getPoint(point)];
}

//functions for finding collision time and point

//note colliders must be already rotated and translated prior to this function
//id1: triangle number
//id2: point number
void pointFaceResolve(int id0,TimeAndId* bestTime,Vector3D pointVelocity,Vector3D* otherPoints,long numOtherPoints){
	double temp;
	double time;
	Triangle* tri;
	for(int t=0;t<this->numTriangles;t++){
		tri=&(this->triangles[t];
		if((temp=V3Ddot(tri->getNormal(),pointVelocity)!=0){
			for(long p=0;p<numOtherPoints;p++){
				time=V3Ddot((this->points[tri->pointA]-otherPoints[p]),tri->getNormal())/temp;
				//TODO CHECK IF POINT IS ACTUALY IN THE TRIANGLE
				if(time<bestTime->time){
					bestTime->time=time;
					bestTime->id0=id0;
					bestTime->id0=t;
					bestTime->id0=p;
				}
			}
		}
	}
}
void edgeEdgeResolveSingle(int id0,int id1,int id2,TimeAndId* bestTime,Vector3D P1,Vector3D P2,Vector3D V1,Vector3D V2,Vector3D Q1,Vector3D Q2,MeshCollider* otherCollider){
	Vector3D normal;
	Vector3D R=Q2-P2;
	Vector3D A=P1-P2;
	Vector3D V=V1-V2;
	Vector3D B=Q1-Q2;
	if(B.x!=0){
		double e1=B.y/B.x;
		double e2=B.z/B.x;
		
		double S1=V2.y-(e1*V2.x)-R.y-(e1*R.x);
		
		double S2=S1*((e2*A.x)-A.z);
		double S3=S1*((e2*V.x)-V.z);
		double S4=(e1*A.x)-A.y;
		double S5=V.y-(e1*V.x);
		double S6=(e2*V2.x)-V2.z;
		double S7=(e2*R.x)-R.z;
		
		double H0=S2+(S4*S7);
		double H1=(S5*S7)-(S4*S6)-S3;
		double H2=-S5*S6;
		double temp=(H1*H1)-(4*H2*H0);
		double t=0;
		double tt;
		bool secondT=false;
		if(H2!=0 && temp>0){
			temp=Math.sqrt(temp);
			if(H1>0){
				t=(temp-H1)/(2*H2);
			}else if(H1<0){
				//two posible cases
				secondT=true;
				t=(-H1+temp)/(2*H2);
				tt=(-H1-temp)/(2*H2);
			}else{
				t=temp/(2*H2);
			}
		}else if(temp=0){
			t=H1/(2*H2);
		}
		if(t>0 && t<bestTime->time){
			//check if collision is on the line
			double a=S1/(S4-(S5*t));
			if(a>=0 && a<=1){
				double b=((a*A.x)+(V.x*a*t)+(V2.x*t)-R.x)/B.x)
				if(b>=0 && b<=1){
					//colision is on the line
					//set new first point of collision
					bestTime->id0=id0;
					bestTime->id1=id1;
					bestTime->id2=id2;
					bestTime->time=t;
				}
			}
		}
		if(secondT){
			if(tt>0 && tt<bestTime->time){
				//check if collision is on the line
				double a=S1/(S4-(S5*tt));
				if(a>=0 && a<=1){
					double b=((a*A.x)+(V.x*a*tt)+(V2.x*tt)-R.x)/B.x)
					if(b>=0 && b<=1){
						//colision is on the line
						//set new first point of collision
						bestTime->id0=id0;
						bestTime->id1=id1;
						bestTime->id2=id2;
						bestTime->time=tt;
					}
				}
			}
		}
	}
}