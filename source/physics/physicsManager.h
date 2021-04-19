#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#includes "collider.h"
#includes "resovableCollider.h"

class PhysicsManager{
	//need list to store colliders
	//both static and dynamic
	//dynamic list should be short
	
	//this with be declaired as a global obj so constructor and destructor is
	//useless because of startup/shutdown order.
	public:
	PhysicsManager();
	void startUp();
	void shutdown();
	~PhysicsManager();
	
	//update function to be called every game loop
	void update(double deltaTime);
	
	//collider list management functions
	void registerCollider(Collider*);
	void unregisterCollider(Collider*);
	
	
	
	
}

#endif