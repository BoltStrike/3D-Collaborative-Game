#include "resolvableCollider.h"
ResolvableCollider::ResolvableCollider():Collider(ColliderType::resVertPill,0.0f,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f)){
	this->pillRad=0.5f;
	this->lineLength=1.0f;
	this->stepup=1.0f;
	this->gravity=10.0f;
	this->setPosition(glm::vec3(0.0f,0.0f,0.0f));
	this->velocity=glm::vec3();
	this->acceleration=glm::vec3();
}
ResolvableCollider::~ResolvableCollider(){}
ResolvableCollider::ResolvableCollider(ColliderType type,float rad,glm::vec3 pos):Collider(type,rad,pos,glm::vec3(0.0f,0.0f,0.0f)){
	this->pillRad=0.5f;
	this->lineLength=1.0f;
	this->stepup=1.0f;
	this->gravity=10.0f;
	this->setPosition(pos);
	this->velocity=glm::vec3();
	this->acceleration=glm::vec3();
}
ResolvableCollider::ResolvableCollider(float rad, float pillRad, float lineLength, float stepup, float gravity, glm::vec3 position):Collider(ColliderType::resVertPill,rad,position,glm::vec3(0.0f,0.0f,0.0f)){
	this->pillRad=pillRad;
	this->lineLength=lineLength;
	this->stepup=stepup;
	this->gravity=gravity;
	this->setPosition(position);
	this->velocity=glm::vec3();
	this->acceleration=glm::vec3();
}
float ResolvableCollider::getBoundingRad(){
	return boundingRad;
}
ColliderType ResolvableCollider::getType(){
	return type;
}
		
		//this is the entry function for detecting collision
bool ResolvableCollider::checkCollision(Collider* oCol){
	if(oCol->checkLine(this->P1,this->P2,this->pillRad))return true;
	if(oCol->checkPoint(this->P1,this->pillRad))return true;
	if(oCol->checkPoint(this->P2,this->pillRad))return true;
	return false;
}
		//There will be functions for resolving collision, though they are not yet implimented or used
		
		
		
		
bool ResolvableCollider::checkLine(glm::vec3 Q1,glm::vec3 Q2){
	//check the line segment (cylender) first
	bool valid;
	float distance=lineToLineDistance(this->P1,this->P2,Q1,Q2,&valid);
	if(valid&&(distance<=this->pillRad))return true;
	//if(distance>this->pillRad)return false;
	
	//check the two endpoints (sphere)
	distance=pointToLineDistance(this->P1,Q1,Q2,&valid);
	if(valid&&(distance<=this->pillRad))return true;
	distance=pointToLineDistance(this->P2,Q1,Q2,&valid);
	if(valid&&(distance<=this->pillRad))return true;
	return false;
}

bool ResolvableCollider::checkLine(glm::vec3 Q1,glm::vec3 Q2,float qrad){
	float jointRad=this->pillRad+qrad;
	//check the line segment (cylender) first
	bool valid;
	float distance=lineToLineDistance(this->P1,this->P2,Q1,Q2,&valid);
	if(valid&&(distance<=jointRad))return true;
	if(distance>this->pillRad)return false;
	
	//check the two endpoints (sphere)
	distance=pointToLineDistance(this->P1,Q1,Q2,&valid);
	if(valid&&(distance<=jointRad))return true;
	distance=pointToLineDistance(this->P2,Q1,Q2,&valid);
	if(valid&&(distance<=jointRad))return true;
	return false;
}

bool ResolvableCollider::checkPoint(glm::vec3 Q){
	//check the line segment (cylender) first
	bool valid;
	float distance=pointToLineDistance(Q,this->P1,this->P2,&valid);
	if(valid&&(distance<this->pillRad))return true;
	if(distance>this->pillRad)return false;
	
	//check the two endpoints (sphere)
	if(glm::distance(Q,P1)<=this->pillRad)return true;
	if(glm::distance(Q,P2)<=this->pillRad)return true;
	return false;
}
bool ResolvableCollider::checkPoint(glm::vec3 Q,float qrad){
	float jointRad=this->pillRad+qrad;
	//check the line segment (cylender) first
	bool valid;
	float distance=pointToLineDistance(Q,this->P1,this->P2,&valid);
	if(valid&&(distance<jointRad))return true;
	if(distance>this->pillRad)return false;
	
	//check the two endpoints (sphere)
	if(glm::distance(Q,P1)<=jointRad)return true;
	if(glm::distance(Q,P2)<=jointRad)return true;
	return false;
}
bool ResolvableCollider::secondaryEdgeCheck(Collider* col){
	return col->checkLine(this->P1,this->P2,this->pillRad);
}


void ResolvableCollider::timeUpdate(float deltaT,std::vector<Collider*>* staticColliders,std::vector<ResolvableCollider*>* dynamicColliders,int selfIndex){
	//Notes on current implimentations: (limitations)
	//dynamic objects cannot collide
	//will mess up if flor and ceiling are one pice (think caves in terain)
	
	
	//Information:
	//There are there positions that will be used
	//1: oldPosition this is where the pill is at the begining of the frame
	//2: targetPosition this is where physics says it should be at the end of the fram if there was no collision
	//		if vertical resalution fails this will be moved back as part of the bianary search
	//3: current position this is where the pill is being tested. It is stored in this->position for collision checking to work
	glm::vec3 oldPosition=this->position;
	glm::vec3 oldVelocity=this->velocity;
	glm::vec3 oldAcceleration=this->acceleration;
	//x_new=0.5*at^2 + vt + x_oldprogram_log("\t\t\tOld position: ");
	glm::vec3 acc=this->acceleration+glm::vec3(0.0f,-gravity,0.0f);
	glm::vec3 accComp=0.5f*deltaT*deltaT*(acc);
	glm::vec3 velComp=deltaT*this->velocity;
	glm::vec3 targetPosition=accComp+velComp+this->position;
	this->setPosition(targetPosition);
	//will worry about velocity latter
	
	//determine the effective step up
	//if the pill is moved up the vertical displacement will be subtracted off to maintain the proper cap
	// the distance the pill can stepup and the heigth loss due to gravity
	float stepupRemainingLineParam=this->stepup+(0.5f*deltaT*deltaT*gravity);
	
	//store the original deltaT
	float totalDeltaT=deltaT;
	//program_log("\t\t\tOld position: ",oldPosition,"\n");
	//program_log("\t\t\tAcceleration: ");
	//program_log(acc);
	//program_log("\n");
	//program_log("\t\t\tVelocity: ",this->velocity,"\n");
	//program_log("\t\t\tAcceleration delta: ");
	//program_log(accComp);
	//program_log("\n");
	//program_log("\t\t\tVelocity delta: ");
	//program_log(velComp);
	//program_log("\n");
	//program_log("\t\t\tCalculated initial test position: ",this->position,"\n");
	
	//loop overview
	//check for collision
	//if collision then verticaly resolve
	//		if sucess then restart collision check loop
	//		if failed then biananry search (halve time)
	//end the loop if no collision or failde search
	
	//loop params
	int searchSplits=3;
	bool didSearch=false;
	bool collision=false;
	float tmpLineParam;
	for(int a=0;a<staticColliders->size();a++){
		//program_log("    Starting Static collider check number: "+std::to_string(a)+"...\n");
		if(staticColliders->at(a)->checkCollision(this)){
			//program_log("      Collision detected with: "+std::to_string(a)+"\n");
			collision=true;
			//atemp resalution
			tmpLineParam=staticColliders->at(a)->resolveVertPillVert(this->P1,this->P2,this->pillRad,stepupRemainingLineParam);//+TINNY_FLOAT_DELTA;
			//program_log("Recived tmpLineParam: "+std::to_string(tmpLineParam)+"\n");
			//program_log("        tmpLineParam: "+std::to_string(tmpLineParam)+"\n");
			if(tmpLineParam<=0.0f){
				//program_log("      Vertical resolution failed\n      Search Splits: "+std::to_string(searchSplits)+"\n");
				//vertical resilution failed;
				//devide deltaT by 2
				deltaT=deltaT/2;
				this->setPosition(0.5f*deltaT*deltaT*(this->acceleration+glm::vec3(0.0f,-gravity,0.0f))+deltaT*this->velocity+oldPosition);
				stepupRemainingLineParam=this->stepup+(0.5f*deltaT*deltaT*gravity);
				searchSplits--;
				didSearch=true;
				if(searchSplits<=0){
					//program_log("\nCollision with: "+std::to_string(a)+"\n\ttmpLineParam: "+std::to_string(tmpLineParam)+" going back to original position\n");
					this->setPosition(oldPosition);
					this->setVelocity(glm::vec3(oldVelocity.x,0.0f,oldVelocity.z));
					this->setAcceleration(glm::vec3());
					return;
				}
				else{
					//program_log("\nCollision with: "+std::to_string(a)+"\n\ttmpLineParam: "+std::to_string(tmpLineParam)+" halved deltaT\n");
					a=-1;
					continue;
				}
			}else{
				//update vertical position
				stepupRemainingLineParam-=tmpLineParam;
				this->setPosition(this->position+glm::vec3(0.0f,tmpLineParam*this->lineLength,0.0f));
			}
			//program_log("        New Position to Try: ",this->position,"\n");
			//a=-1;
			//continue;
		}
	}
	//program_log("    done with collisions\n");
	//figure out what to do with velocity
	glm::vec3 targetVelocity=deltaT*(this->acceleration+glm::vec3(0.0f,-gravity,0.0f))+this->velocity;
	if(didSearch)this->velocity=targetVelocity+deltaT*glm::vec3(0.0f,gravity,0.0f);
	else if(!collision)this->velocity=targetVelocity;
	if(this->velocity.y < -10.0f)this->velocity.y=-10.0f;
}


void ResolvableCollider::setStepup(float su){
	this->stepup=su;
}
float ResolvableCollider::getStepup(){
	return this->stepup;
}
void ResolvableCollider::setGravity(float grav){
	this->gravity=grav;
}
float ResolvableCollider::getGravity(){
	return this->gravity;
}
//motion paramiters
void ResolvableCollider::setPosition(glm::vec3 pos){
	this->position=pos;
	this->P1=pos+glm::vec3(0.0f,-lineLength/2,0.0f);
	this->P2=pos+glm::vec3(0.0f,lineLength/2,0.0f);
}
glm::vec3 ResolvableCollider::getPosition(){
	return this->position;
}
void ResolvableCollider::setRotation(glm::vec3){} //does nothing
glm::vec3 ResolvableCollider::getRotation(){
	return glm::vec3();
}
void ResolvableCollider::setVelocity(glm::vec3 vel){
	this->velocity=vel;
}
glm::vec3 ResolvableCollider::getVelocity(){
	return this->velocity;
}
void ResolvableCollider::setAcceleration(glm::vec3 acc){
	this->acceleration=acc;
}
glm::vec3 ResolvableCollider::getAcceleration(){
	return this->acceleration;
}