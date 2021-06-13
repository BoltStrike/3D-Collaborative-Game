#include "colliderLoader.h"

Collider* loadCollider(const char *filepath){
	//this is not in the parrent class b/c of circular includes
	//this will decide on the collider type
	//first line will be: type radi
	//pass the stream into the collider
	std::string type;
	float rad;
	std::stringstream stream = file_tosstream(filepath);// Store file as stream
	stream>>type;
	stream>>rad;
	if(type=="infPlane"){
		return new InfPlaneCollider(&stream, rad);
	}else if(type=="plane"){
		return new PlaneCollider(&stream, rad);
	}else if(type=="sphere"){
		return new SphereCollider(&stream, rad);
	}else if(type=="box"){
		return new BoxCollider(&stream, rad);
	}else if(type=="mesh"){
		return new MeshCollider(&stream, rad);
	}
	return NULL;
}