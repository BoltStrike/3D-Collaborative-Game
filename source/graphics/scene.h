
#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <sstream>

#include "object.h"
#include "window.h"
#include "../generic/file_tosstream.h"

class Scene {
	private:
		std::string name;			// Name of scene
		Object *objects;			// Array holding all objects in the scene
		unsigned int num_objects;	// Number of objects in the scene
		unsigned int VAO;			// Vertex array ID for OpenGL
		
	public:
		Scene();					// Default constructor
		~Scene();					// Default destructor
		void load(const char*);		// Loads the scene
		void draw();				// Draw the scene			
};
#endif
