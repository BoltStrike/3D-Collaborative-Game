
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <sstream>

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "mesh.h"
#include "material.h"

class Object{
	private:
		
		
		std::string name;	// Name of the object
		glm::vec3 position;	// Position of the object in the scene
		glm::vec3 rotation;	// Rotation of the object in the scene (radians)
		glm::vec3 scale;	// Scale of the object in the scene

		unsigned int VBO;	// Vertex buffer ID
		unsigned int VAO;	// Vertex array ID
		
	public:
		Material *mat;	// Material of the object
		Mesh *mesh; 	// Mesh of the object
	
		Object();				// Default constructor
		void load(const char*);	// Loads the object 
		void compile();			// Link current object to OpenGL
		void draw();			// Draws the object in its current state
		
		void set_name(std::string);		// Set the name
		std::string get_name()const;	// Get the name
		
		void set_position(glm::vec3);	// Set position
		glm::vec3 get_position()const;	// Get position
		void translate(glm::vec3);		// Translate object by given vector 

		void set_rotation(glm::vec3);	// Set rotation
		glm::vec3 get_rotation()const;	// Get rotation
		void rotate(glm::vec3);			// Rotate object by given vector

		void set_scale(glm::vec3);		// Set scale
		glm::vec3 get_scale()const;		// Get scale
		void dilate(glm::vec3);			// Dilate object by given vector
		
};
#endif
