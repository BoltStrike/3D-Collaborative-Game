#include "meshCollider.h"

MeshCollider::MeshCollider():Collider(ColliderType::mesh,0.0f,glm::vec3(),glm::vec3()){
	this->pointList=NULL;
	this->numPoints=0;
	this->triangleList=NULL;
	this->numTriangles=0;
}
MeshCollider::~MeshCollider(){
	free(pointList);
	free(triangleList);
}

MeshCollider::MeshCollider(glm::vec3* pointList,int numPoints, int* triangleList, int numTriangles, float rad,glm::vec3 pos, glm::vec3 rot):Collider(ColliderType::mesh,rad,pos,rot){
	this->pointList=pointList;
	this->numPoints=numPoints;
	this->triangleList=triangleList;
	this->numTriangles=numTriangles;
}
MeshCollider::MeshCollider(const char* filepath,float rad,glm::vec3 pos, glm::vec3 rot):Collider(ColliderType::mesh,rad,pos,rot){
	Ubj f;
	f.open(filepath);

	//get the points/vertxes
	f = f.beginning().at("number of positions");
	numPoints = f.get_l();
	f = f.beginning().at("positions");
	pointList = new glm::vec3[numPoints];		// Allocate position storage
	for (int i = 0; i < numPoints; i++) {	// Store position data
		pointList[i] = glm::vec3(f.get_f(), f.get_f(), f.get_f());
	}

	f = f.beginning().at("number of faces");
	numTriangles = f.get_l();
	f = f.beginning().at("indices");
	triangleList = new int[numTriangles * 3];		// 3 vertex indices (points) per face (triangle)
	for (int i = 0; i < numTriangles * 3; i++) { 	// Store indices
		triangleList[i] = f.get_l();
	}

	f.close();

	this->setRotation(rot);
	this->setPosition(pos);
}
MeshCollider::MeshCollider(const MeshCollider &other){
	this->numPoints=other.numPoints;//getNumPoints();
	this->numTriangles=other.numTriangles;//getNumTriangles();
	this->pointList=(glm::vec3*) malloc(numPoints*sizeof(glm::vec3));
	glm::vec3* otherPoints=other.pointList;//getPointList();
	for(int a=0;a<numPoints;a++){
		this->pointList[a]=otherPoints[a];
	}
	this->triangleList=(int*) malloc(numTriangles*3*sizeof(int));
	int* otherTriangles=other.triangleList;//getTriangleList();
	for(int b=0;b<numTriangles*3;b++){
		this->triangleList[b]=otherTriangles[b];
	}
}
glm::vec3* MeshCollider::getPointList(){return this->pointList;}
int MeshCollider::getNumPoints(){return this->numPoints;}
int* MeshCollider::getTriangleList(){return this->triangleList;}
int MeshCollider::getNumTriangles(){return this->numTriangles;}

bool MeshCollider::checkCollision(Collider* oCol){
	bool returnVal=false;
	//this ends up checking every line twice
	//maybe fix so there is a list of edges
	//program_log("        number of points in mesh: "+std::to_string(this->numPoints)+"\n");
	for(int i=0;i<numTriangles;i++){
		//program_log("        checking triange: "+std::to_string(i)+"\n");
		if(oCol->checkLine(getPoint(i,0),getPoint(i,1))){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 0&1: ");
			program_log(getPoint(i,0));
			program_log("&");
			program_log(getPoint(i,1));
			program_log("\n");*/
			return true;//returnVal=true;
		}
		if(oCol->checkLine(getPoint(i,1),getPoint(i,2))){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 1&2: ");
			program_log(getPoint(i,1));
			program_log("&");
			program_log(getPoint(i,2));
			program_log("\n");*/
			return true;//returnVal=true;
		}
		if(oCol->checkLine(getPoint(i,2),getPoint(i,0))){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 2&0: ");
			program_log(getPoint(i,2));
			program_log("&");
			program_log(getPoint(i,0));
			program_log("\n");*/
			return true;//returnVal=true;
		}
	}
	//if(returnVal)return true;
	return oCol->secondaryEdgeCheck(this);
}
bool MeshCollider::checkLine(glm::vec3 q1,glm::vec3 q2){
	//check against each triangle
	glm::vec3 collisionPoint;
	glm::vec3 normal;
	float totalArea2;
	float sumArea2;
	bool valid;
	for(int i=0;i<numTriangles;i++){
		normal=glm::cross(getPoint(i,1)-getPoint(i,0),getPoint(i,2)-getPoint(i,0));
		totalArea2=glm::length(normal);
		collisionPoint=lineAndPlaneIntersection(q1,q2,getPoint(i,0),normal/totalArea2,&valid);
		if(valid&&areaCheck(collisionPoint,i,totalArea2))return true;
	}
	return false;
}
bool MeshCollider::checkLine(glm::vec3 q1,glm::vec3 q2,float rad){
	//check cylender
	glm::vec3 collisionPoint;
	glm::vec3 normal;
	float totalArea2;
	float sumArea2;
	bool valid;
	for(int i=0;i<numTriangles;i++){
		//check plane
		normal=glm::cross(getPoint(i,1)-getPoint(i,0),getPoint(i,2)-getPoint(i,0));
		totalArea2=glm::length(normal);
		collisionPoint=lineAndPlaneIntersection(q1,q2,getPoint(i,0),normal/totalArea2,&valid);
		if(valid&&areaCheck(collisionPoint,i,totalArea2)){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Plane Points 1&2&3: ",getPoint(i,0),"");
			program_log("&",getPoint(i,1),"");
			program_log("&",getPoint(i,2),"\n");*
			return true;
		}
		//check line
		if((lineToLineDistance(getPoint(i,0),getPoint(i,1),q1,q2,&valid)<=rad)&& valid){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 0&1: ");
			program_log(getPoint(i,0));
			program_log("&");
			program_log(getPoint(i,1));
			program_log("\n");*/
			return true;
		}
		if((lineToLineDistance(getPoint(i,1),getPoint(i,2),q1,q2,&valid)<=rad)&& valid){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 1&2: ");
			program_log(getPoint(i,1));
			program_log("&");
			program_log(getPoint(i,2));
			program_log("\n");*/
			return true;
		}
		if((lineToLineDistance(getPoint(i,2),getPoint(i,0),q1,q2,&valid)<=rad)&& valid){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 2&0: ");
			program_log(getPoint(i,2));
			program_log("&");
			program_log(getPoint(i,0));
			program_log("\n");*/
			return true;
		}
	}
	//check point
	for(int i=0;i<numPoints;i++){
		if((pointToLineDistance(pointList[i],q1,q2,&valid)<=rad)&&valid){
			//program_log("        Collision, Point: "+std::to_string(i)+": ",pointList[i],"\n");
			return true;
		}
	}
	//check both sphears
	if(this->checkPoint(q1,rad)){
		//program_log("/t/tPoint with problem: Q1: ",q1,"/n");
		return true;
	}
	if(this->checkPoint(q2,rad)){
		//program_log("/t/tPoint with problem: Q2: ",q2,"/n");
		return true;
	}
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
		normal=glm::cross(getPoint(i,1)-getPoint(i,0),getPoint(i,2)-getPoint(i,0));
		area2=glm::length(normal);
		dist=glm::dot(point-getPoint(i,0),normal)/area2;
		if(abs(dist)<=rad){
			//find projected point
			//check area
			if(areaCheck(point-(dist*normal/area2),i,area2)){
				/*program_log("        Collision, Triangle: "+std::to_string(i)+"Plane Points 1&2&3: ",getPoint(i,0),"");
				program_log("&",getPoint(i,1),"");
				program_log("&",getPoint(i,2),"\n");*/
				return true;
			}
		}
		//check against edges
		//check distance
		//check if on line segment
		if(pointLineCheck(point,rad,i,0,1)){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 0&1: ");
			program_log(getPoint(i,0));
			program_log("&");
			program_log(getPoint(i,1));
			program_log("\n");*/
			return true;
		}
		if(pointLineCheck(point,rad,i,1,2)){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 1&2: ");
			program_log(getPoint(i,1));
			program_log("&");
			program_log(getPoint(i,2));
			program_log("\n");*/
			return true;
		}
		if(pointLineCheck(point,rad,i,2,0)){
			/*program_log("        Collision, Triangle: "+std::to_string(i)+"Points 2&0: ");
			program_log(getPoint(i,2));
			program_log("&");
			program_log(getPoint(i,0));
			program_log("\n");*/
			return true;
		}
	}
	
	//check against points
	for(int b=0;b<numPoints;b++){
		if(glm::length(point-pointList[b])<=rad){
			//program_log("        Collision, Point: "+std::to_string(b)+": ",pointList[b],"\n");
			return true;
		}
	}
	return false;
}


//resolving functions
float MeshCollider::resolveVertPillVert(glm::vec3 P1,glm::vec3 P2,float rad,float maxLineParam){
	//max Line param is the adjusted step up distance
	//variable for the current amount of vertical shift
	float currentLineParam=-1.0f;
	//intermediate variables
	//capital is vector, lowercase is scalar
	glm::vec3 A,B,C,D,E,N;
	glm::vec3 P2mP1=P2-P1;
	float a,b,c,a1,a2;
	float tmpResualt;
	//resolve points
	a=glm::dot(P2mP1,P2mP1);
	float determinate;
	//go throught the points
	for(int i=0;i<this->numPoints;i++){
		//determine the value
		b=2*glm::dot(P2mP1,P1-this->pointList[i]);
		c=glm::dot(P1-this->pointList[i],P1-this->pointList[i])-(rad*rad); //glm::dot(this->pointList[i],this->pointList[i])+glm::dot(P1,P2mP1-this->pointList[i])-(rad*rad)
		determinate=b*b-(4*a*c);
		if(determinate>=0){
			//there will be two resualts
			//always use the larger one
			tmpResualt=(-b+sqrt(determinate))/(2*a);
			if(currentLineParam<tmpResualt){
				currentLineParam=tmpResualt;
				//program_log("        New line param: "+std::to_string(currentLineParam)+"\n"+"          Using point number "+std::to_string(i)+" = ",this->pointList[i],"\n");
			}
		}
	}
	
	
	//resolve lines
	//resolve planes
	//go thourgh the planes
	for(int i=0;i<numTriangles;i++){
		//go thourgh the lines first
		currentLineParam=this->resolveLineVertPillVert(P1,P2,rad,this->getPoint(i,0),this->getPoint(i,1),currentLineParam);
		currentLineParam=this->resolveLineVertPillVert(P1,P2,rad,this->getPoint(i,1),this->getPoint(i,2),currentLineParam);
		currentLineParam=this->resolveLineVertPillVert(P1,P2,rad,this->getPoint(i,2),this->getPoint(i,0),currentLineParam);
		//now deal with the plane
		//get the distance
		//A=P1-this->getPoint(i,0);
		/*program_log("          Using plane (triangle) number "+std::to_string(i)+" = ");
		program_log(this->getPoint(i,0));
		program_log(" , ");
		program_log(this->getPoint(i,1));
		program_log(" , ");
		program_log(this->getPoint(i,2));
		program_log("\n");*/
		N=this->getNormal(i);
		//program_log("          N: ",N,"\n");
		b=glm::length(N);
		//program_log("          b: "+std::to_string(b)+"\n");
		a=((rad*b)-glm::dot(N,P1-this->getPoint(i,0)))/(N.y*(P2.y-P1.y));
		//program_log("          a: "+std::to_string(a)+"\n");
		A=P1+((P2-P1)*a)-(N*rad)/b;
		//program_log("          A: ",A,"\n");
		if(this->areaCheck(A,i,b)){
			//program_log("          cleared area check\n");
			if(a>currentLineParam){
				currentLineParam=a;
				//program_log("        New line param: "+std::to_string(currentLineParam)+"\n"+"          Using plane (triangle) number "+std::to_string(i)+" = ",this->getPoint(i,0)," , ");
				//program_log("",this->getPoint(i,1)," , ");
				//program_log("",this->getPoint(i,2),"\n");
			}
		}
		/*b=glm::dot(N,this->getPoint(i,0)-P1);
		a1=(b+(rad*glm::length(N)))/N.y;
		a2=(b+(rad*glm::length(N)))/N.y;
		a=(a1>a2)?a1:a2;
		if(a>0){
			//check if in the plane
			//find P1 prime (C)
			C=P1+glm::vec3(0.0f,a*(P2.y-P1.y),0.0f);
			//find Q prime (D)
			D=P1+((N.y>0)?(-rad*N/glm::length(N)):(rad*N/glm::length(N)));
			if(this->areaCheck(D,i,glm::length(N))){
				//the point is on the plane
				currentLineParam=a;
				program_log("        New line param: "+std::to_string(currentLineParam)+"\n");
				program_log("          Using plane (triangle) number "+std::to_string(i)+" = ");
				program_log(this->getPoint(i,0));
				program_log(" , ");
				program_log(this->getPoint(i,1));
				program_log(" , ");
				program_log(this->getPoint(i,2));
				program_log("\n");
			}
		}*/
	}
	//if(maxLineParam<currentLineParam) return -1.0;
	/*else*/ return currentLineParam;	
}
float MeshCollider::resolveLineVertPillVert(glm::vec3 P1, glm::vec3 P2, float rad, glm::vec3 Q1, glm::vec3 Q2, float maxLineParam){
	glm::vec3 A,B,C,D,E;
	float b,c,d=-1.0f,de,f;
	A=P1-Q1;
	B=Q2-Q1;
	C=glm::vec3(0.0f,P2.y-P1.y,0.0f); //P2.x=P1.x and P2.z=P1.z
	b=glm::dot(A,B);
	c=C.y*B.y;
	D=A-b*B;
	E=C-c*B;
	de=glm::dot(D,E);
	float determ=(de*de)-glm::dot(E,E)*(glm::dot(D,D)-(rad*rad));
	float resualt=-1.0f;
	if(determ>0.0f)resualt=(-de+sqrt(determ))/glm::dot(E,E);
	else if(determ==0.0f)resualt=-de/glm::dot(E,E);
	if(resualt>maxLineParam){
		//check that the resilotion is on the line
		if(B.x!=0){
			d=(D.x-Q1.x+(resualt*E.x))/B.x;
		}else if(B.y!=0){
			d=(D.y-Q1.y+(resualt*E.y))/B.y;
		}else if(B.z!=0){
			d=(D.z-Q1.z+(resualt*E.z))/B.z;
		}else{
			program_log("ERROR:\n Section: Physics Engine\n Class: meshCollider\n Function: resolveLineVertPillVert\n");
			program_log(" REASON: line of zero length:\n");
			program_log("  Q1: ",Q1,"\n");
			program_log("  Q2: ",Q2,"\n");
			program_log(" More info:\n  Number of points in collider: "+std::to_string(this->numPoints)+"\n  Number of triangles in collider: "+std::to_string(this->numTriangles)+"\n");
			program_log(" Posible fixes:\n  Check mesh file for repeat points\n  Check collider local to global cordinates conversion\n  Reduce triangle/point count\n  re export mesh file");
			
		}
		if(isBetween0and1(d)){
			/*program_log("        New line param: "+std::to_string(resualt)+"\n          Using line = ");
			program_log(Q1);
			program_log(" , ",Q2,"\n");
			program_log("          A: ",A,"\n");
			program_log("          B: ",B,"\n");
			program_log("          C: ",C,"\n");
			program_log("          D: ",D,"\n");
			program_log("          E: ",E,"\n");
			program_log("          b: "+std::to_string(b)+"\n");
			program_log("          c: "+std::to_string(c)+"\n");
			program_log("          de: "+std::to_string(de)+"\n");
			program_log("          d: "+std::to_string(d)+"\n");
			program_log("          determ: "+std::to_string(determ)+"\n");*/
			return resualt;
		}
	}
	return maxLineParam;
	/*A=P1-Q1;
	B=Q2-Q1;
	C=P2-P1;
	D=glm::cross(A,B);
	E=glm::cross(C,B);
	f=glm::dot(E,D);
	float determinate=(f*f)-(glm::dot(E,E)*(glm::dot(D,D))-(rad*rad*glm::dot(B,B)));
	if(determinate<=0)return maxLineParam;
	float resualt=(-f+sqrt(determinate))/glm::dot(E,E);
	//check if the point on the msehc line falls in the segment
	if(isBetween0and1(2*glm::dot(resualt*C+A,B)/glm::dot(B,B))){
		if(resualt>maxLineParam){
			program_log("        New line param: "+std::to_string(resualt)+"\n");
			program_log("          Using line = ");
			program_log(Q1);
			program_log(" , ");
			program_log(Q2);
			program_log("\n");
		}
		return (resualt>maxLineParam)?resualt:maxLineParam;
	}
	else return maxLineParam;*/
}


bool MeshCollider::secondaryEdgeCheck(Collider* oCol){
	//this is the same as the main check, though can leave out one edge per triangle
	//this sometimes ends up checking lines twice
	for(int i=0;i<numTriangles;i++){
		if(oCol->checkLine(getPoint(i,0),getPoint(i,1)))return true;
		if(oCol->checkLine(getPoint(i,1),getPoint(i,2)))return true;
	}
	return false;
}

//area2 is because the length of the cross product is the area of a paralleligram, so the actual triangle area is half that
//this save a tiny bit of floating point opperations by not deviding by 2
inline bool MeshCollider::areaCheck(glm::vec3 point,int tri,float area2){
	float areaSum2 =glm::length(glm::cross(point-getPoint(tri,0),getPoint(tri,1)-getPoint(tri,0)));
	areaSum2+=glm::length(glm::cross(point-getPoint(tri,1),getPoint(tri,2)-getPoint(tri,1)));
	areaSum2+=glm::length(glm::cross(point-getPoint(tri,2),getPoint(tri,0)-getPoint(tri,2)));
	//program_log("/t/tareaSum2="+std::to_string(areaSum2)+"/n/t/tarea2="+std::to_string(area2)+"/n");
	return floatsAreEqual(area2,areaSum2);
}
inline bool MeshCollider::pointLineCheck(glm::vec3 point,float rad,int tri,int a,int b){
	bool valid=false;
	float dist=pointToLineDistance(point,getPoint(tri,a),getPoint(tri,b),&valid);
	return (dist<=rad)&&valid;
}
inline glm::vec3 MeshCollider::getPoint(int a,int b){
	//char buffer[50];
	//sprintf(buffer,"\t\t\ttriange list address %p\n",triangleList);
	//program_log(buffer);
	//program_log("          Retrived triangle point number: ("+std::to_string(a)+","+std::to_string(b)+")="+std::to_string((3*a)+b));
	int pointNumber=this->triangleList[(3*a)+b];
	//program_log(" point number: "+std::to_string(pointNumber));
	glm::vec3 point =this->pointList[pointNumber];
	//program_log(" value: ("+std::to_string(point.x)+", "+std::to_string(point.y)+", "+std::to_string(point.z)+")\n");
	return point;
}
inline glm::vec3 MeshCollider::getNormal(int n){
	return glm::cross(getPoint(n,1)-getPoint(n,0),getPoint(n,2)-getPoint(n,0));
}

void MeshCollider::setPosition(glm::vec3 pos){
	//shift everypoint in the mesh back to the orgin then to the new location
	for(int a=0;a<numPoints;a++){
		this->pointList[a]=this->pointList[a]+pos-this->position;
	}
	this->position=pos;
}
glm::vec3 MeshCollider::getPosition(){
	return this->position;
}
void MeshCollider::setRotation(glm::vec3 rot){
	//Big TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
	//account for a non zero position
	//sill want to rotate arround obj center
	this->rotation=rot;
}
glm::vec3 MeshCollider::getRotation(){
	return this->rotation;
}

void MeshCollider::printTriangles(){
	for(int i = 0; i < 3*numTriangles; i++){ 	// Store indices
		program_log("("+std::to_string(i)+","+std::to_string(triangleList[i])+") ");
	}
	program_log("\n");
}