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
MeshCollider::MeshCollider(std::stringstream* stream1,float rad,glm::vec3 pos, glm::vec3 rot):Collider(ColliderType::mesh,rad,pos,rot){
	//this will refrence a mesh file for easy blender export
	std::string materialPath;
	(*stream1)>>materialPath;
	program_log("\t\tSkiping material file: ");
	program_log(materialPath);
	program_log("\n");
	std::string meshPath;
	(*stream1)>>meshPath;
	program_log("\t\tReading mesh file: ");
	program_log(meshPath);
	program_log("\n");
	//taken form the graphics/mesh class
	//std::stringstream stream = file_tosstream(filepath);// Read file as stream
	std::stringstream stream = file_tosstream(meshPath.c_str());// Store file as stream
	int name_length;
	stream >> name_length;					// Get the length of the name
	std::string name = new char[name_length + 1]; 		// +1 for terminating char '\0'
	name[name_length] = '\0';				// Set terminating char
	for(int i = 0; i < name_length; i++)	// Store name
		stream.get(name[i]);

	stream >> numPoints;	// Get the number of vertices
	
	float x,y,z;
	this->pointList = new glm::vec3[numPoints];		// Allocate position storage
	for(int i = 0; i < numPoints; i++){	// Store position data
		stream >> x>>y>>z;
		pointList[i]=glm::vec3(x,y,z);
	}
	
	program_log("\t\t\tRecordered Point Data");
	
	float normal;
	for(int i = 0; i < numPoints * 3; i++)	// Store normal data
		stream >> normal;
	
	program_log("\t\t\tRecordered Normal Data");
	
	int num_uvs;
	stream >> num_uvs;						// Get the number of UV coordinates
	float uv;			// Allocate enough UV storage
	for(int i = 0; i < num_uvs * 2; i++)	// Store all UV coordinates
		stream >> uv;

	program_log("\t\t\tRecordered UV Data");

	stream >> numTriangles;					// Get the number of faces
	this->triangleList = new int[numTriangles*3];		// 3 vertex indices per face
	for(int i = 0; i < 3*numTriangles; i++){ 	// Store indices
		stream >> triangleList[i];
	}
	if(numPoints==343){
		for(int i = 0; i < 3*numTriangles; i++){ 	// Store indices
			program_log("("+std::to_string(i)+","+std::to_string(triangleList[i])+") ");
		}
	}
	
	program_log("\t\t\tRecordered triangle Data");
	char buffer[50];
	sprintf(buffer,"\t\t\ttriange list address %p\n",triangleList);
	program_log(buffer);
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
	//this ends up checking every line twice
	//maybe fix so there is a list of edges
	program_log("        number of points in mesh: "+std::to_string(this->numPoints)+"\n");
	for(int i=0;i<numTriangles;i++){
		program_log("        checking triange: "+std::to_string(i)+"\n");
		if(oCol->checkLine(getPoint(i,0),getPoint(i,1)))return true;
		if(oCol->checkLine(getPoint(i,1),getPoint(i,2)))return true;
		if(oCol->checkLine(getPoint(i,2),getPoint(i,0)))return true;
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
		normal=glm::cross(getPoint(i,1)-getPoint(i,0),getPoint(i,2)-getPoint(i,0));
		totalArea2=glm::length(normal);
		if(checkLineSegmentPlane(q1,q2,normal/totalArea2,getPoint(i,0),&collisionPoint)&&areaCheck(collisionPoint,i,totalArea2))return true;
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
		normal=glm::cross(getPoint(i,1)-getPoint(i,0),getPoint(i,2)-getPoint(i,0));
		area2=glm::length(normal);
		dist=glm::dot(point-getPoint(i,0),normal)/area2;
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


//resolving functions
float MeshCollider::resolveVertPillVert(glm::vec3 P1,glm::vec3 P2,float rad,float maxLineParam){
	//max Line param is the adjusted step up distance
	//variable for the current amount of vertical shift
	float currentLineParam=0.0;
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
		c=glm::dot(this->pointList[i],this->pointList[i])+glm::dot(P1,P2mP1-this->pointList[i])-(rad*rad);
		determinate=b*b-(4*a*c);
		if(determinate>0){
			//there will be two resualts
			//always use the larger one
			tmpResualt=(-b+sqrt(determinate))/(2*a);
			if(currentLineParam<tmpResualt)currentLineParam=tmpResualt;
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
		N=this->getNormal(i);
		b=glm::dot(N,this->getPoint(i,0)-P1);
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
			}
		}
	}
	if(maxLineParam<currentLineParam) return -1.0;
	else return currentLineParam;	
}
float MeshCollider::resolveLineVertPillVert(glm::vec3 P1, glm::vec3 P2, float rad, glm::vec3 Q1, glm::vec3 Q2, float maxLineParam){
	glm::vec3 A,B,C,D,E;
	float f;
	A=P1-Q1;
	B=Q2-Q1;
	C=P2-P1;
	D=glm::cross(A,B);
	E=glm::cross(C,B);
	f=glm::dot(E,D);
	float determinate=(f*f)-(glm::dot(E,E)*(glm::dot(D,D))-(rad*rad*glm::dot(B,B)));
	if(determinate<=0)return maxLineParam;
	float resualt=(-f+sqrt(determinate))/glm::dot(E,E);
	//check if the point on the msehc line falls in the segment
	if(isBetween0and1(2*glm::dot(resualt*C+A,B)/glm::dot(B,B))) return (resualt>maxLineParam)?resualt:maxLineParam;
	else return maxLineParam;
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
inline bool MeshCollider::areaCheck(glm::vec3 point,int tri,float area2){
	float areaSum2 =glm::length(glm::cross(point-getPoint(tri,0),getPoint(tri,1)-getPoint(tri,0)));
	areaSum2+=glm::length(glm::cross(point-getPoint(tri,1),getPoint(tri,2)-getPoint(tri,1)));
	areaSum2+=glm::length(glm::cross(point-getPoint(tri,2),getPoint(tri,0)-getPoint(tri,2)));
	return floatsAreEqual(area2,areaSum2);
}
inline bool MeshCollider::pointLineCheck(glm::vec3 point,float rad,int tri,int a,int b){
	float dist=getPointToLineDistance(point,getPoint(tri,a),getPoint(tri,b));
	if(dist<=rad){
		if(isBetween0and1(glm::length(glm::dot(getPoint(tri,b)-getPoint(tri,a),point-getPoint(tri,a)))/
				glm::length(getPoint(tri,b)-getPoint(tri,a))))return true;
	}
	return false;
}
inline glm::vec3 MeshCollider::getPoint(int a,int b){
	char buffer[50];
	sprintf(buffer,"\t\t\ttriange list address %p\n",triangleList);
	program_log(buffer);
	program_log("          Retrived triangle point number: ("+std::to_string(a)+","+std::to_string(b)+")="+std::to_string((3*a)+b));
	int pointNumber=this->triangleList[(3*a)+b];
	program_log(" point number: "+std::to_string(pointNumber));
	glm::vec3 point =this->pointList[pointNumber];
	program_log(" value: ("+std::to_string(point.x)+", "+std::to_string(point.y)+", "+std::to_string(point.z)+")\n");
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