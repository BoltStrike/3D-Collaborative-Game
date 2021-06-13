#ifndef OBJECT_ID_MANAGER
#define OBJECT_ID_MANAGER

class ObjectIDManager{
	private:
	Object** lookupTable;
	int lookupTableSize;
	int lowestAvailableID;
	
	public:
	ObjectIDManager();
	void startUp();
	void shutdown();
	~ObjectIDManager();
	
	//usefull functions
	int registerObject(Object*);
	Object* unregisterOject(int);
	
	//get the pointer to the object base on the ID
	Object* getObject(int);
	
}


#endif