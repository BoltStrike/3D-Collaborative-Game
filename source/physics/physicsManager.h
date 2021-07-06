#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include "collider.h"
#include "resolvableCollider.h"
#include <vector>
#include "../generic/program_log.h"

class PhysicsManager{
	//need list to store colliders
	//both static and dynamic
	//dynamic list should be short
	//std::vector is a palaceholder it should be replaced with someting better
	//the staticCollider list will not change much (only removal?)
	std::vector<Collider*> staticColliders;
	std::vector<ResolvableCollider*> dynamicColliders;
	
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
	
	
	
	
};

#endif