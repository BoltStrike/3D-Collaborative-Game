#ifndef COLLISON_CALLBACK
#define COLLISON_CALLBACK

//this is an interface class it is inteded to be used to notify objecs
//that they hava collided. The objects will then determine what will happen next.

//order may matter on what actualy happens

public CollisionCallback{
	public:
	//this function will be called when an object has a collision
	virtual collisionCallback();
}

#endif