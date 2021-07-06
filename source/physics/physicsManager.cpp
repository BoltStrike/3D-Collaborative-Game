#include "physicsManager.h"
PhysicsManager::PhysicsManager(){}
void PhysicsManager::startUp(){
	staticColliders=std::vector<Collider*>();
	dynamicColliders=std::vector<ResolvableCollider*>();
}
void PhysicsManager::shutdown(){
	if(staticColliders.size()!=0){
		for(int a=0;a<staticColliders.size();a++){
			delete staticColliders.at(a);
		}
	}
	if(dynamicColliders.size()!=0){
		for(int a=0;a<dynamicColliders.size();a++){
			delete dynamicColliders.at(a);
		}
	}
}
PhysicsManager::~PhysicsManager(){
	this->shutdown();
}
	
	//update function to be called every game loop
void PhysicsManager::update(double deltaTime){
	for(int a=0;a<dynamicColliders.size();a++){
		//go through each dynamic collider for tit to update and reslove its position
		//everything is haddeled internaly to the collider
		program_log("\t\tUpdating dynamic collider: ");
		program_log(std::to_string(a).c_str());
		program_log("...\n");
		this->dynamicColliders.at(a)->timeUpdate(deltaTime,&staticColliders,&dynamicColliders,a);
		program_log("\t\tUpdated dynamic collider: ");
		program_log(std::to_string(a).c_str());
		program_log("\n");
	}
}
	
	//collider list management functions
void PhysicsManager::registerCollider(Collider* col){
	//check if the collider is resovable/dynamic;
	if(col->getType()==ColliderType::resVertPill){
		dynamicColliders.push_back((ResolvableCollider*) col);
	}else{
		staticColliders.push_back(col);
	}
}
void PhysicsManager::unregisterCollider(Collider* col){
	//find the collider
	//start with the dynamic suf first (projectiles)
	for(int a=0;a<dynamicColliders.size();a++){
		if(dynamicColliders.at(a)==(ResolvableCollider*)col){
			dynamicColliders.erase(dynamicColliders.begin()+a);
		}
	}
	for(int a=0;a<staticColliders.size();a++){
		if(staticColliders.at(a)==col){
			staticColliders.erase(staticColliders.begin()+a);
		}
	}
}
	