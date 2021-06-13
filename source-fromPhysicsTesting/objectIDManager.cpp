#include "objectIDManager.h"
ObjectIDManager::ObjectIDManager(){}
void ObjectIDManager::startUp(){
	this->lookupTable=new Object**[64];
	this->lookupTableSize=64;
	this->lowestAvailableID=0;
}
void ObjectIDManager::shutdown(){
	delete this->lookupTable;
}
ObjectIDManager::~ObjectIDManager(){}

//usefull functions
int ObjectIDManager::registerObject(Object* toRegister){
	//find first available ID
	int lookingAtID=this->lowestAvailableID;
	do{
		if(this->lookupTable[lookingAtID]==NULL){
			//found an availible ID
			//populate it
			this->lookupTable[lookingAtID]=toRegister;
			this->lowestAvailableID=lookingAtID;
			return lookingAtID
		}
		++lookingAtID;
	}while(lookingAtID<this->lookupTableSize);
	//there is no availible space in the table at this point
	//time to cry
	//get a buffer with twice the current size
	Object** oldTable=this->lookupTable;
	this->lookupTable=malloc(sizeof(Object*)*this->lookupTableSize*2);
	//start the coppy
	for(int a=0;a<lookupTableSize;a++){
		this->lookupTable[a]=oldTable[a];
	}
	this->lookupTable[this->lookupTableSize]=toRegister;
	this->lowestAvailableID=this->lookupTableSize+1;
	this->lookupTableSize*=2;
	return this->lowestAvailableID-1;
}
Object* ObjectIDManager::unregisterOject(int idToUnregister){
	this->lookupTable[idToUnregister]=NULL;
	if(idToUnregister<this->lowestAvailableID)this->lowestAvailableID=idToUnregister;
}
	
//get the pointer to the object base on the ID
Object* ObjectIDManager::getObject(int objID){
	return this->lookupTable[objID];
}