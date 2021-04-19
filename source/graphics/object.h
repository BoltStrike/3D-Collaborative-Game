
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <sstream>

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../../glm/gtx/quaternion.hpp"

#include "mesh.h"
#include "material.h"

class Object{
	private:
		std::string name;	// Name of the object
		glm::vec3 location;	// Position of the object in the scene
		glm::vec3 rotation;	// Rotation of the object in the scene (radians)
		glm::vec3 dilation;	// Scale of the object in the scene

		unsigned int VBO;			// Vertex buffer ID
		unsigned int VAO;			// Vertex array ID
		unsigned int instanceVBO;	// Instance buffer ID

		unsigned int num_instances;
		glm::vec3 *translations;
		
	public:
		Material *mat;	// Material of the object
		Mesh *mesh; 	// Mesh of the object
	
		Object();				// Default constructor
		~Object();				// Default destructor
		// Loads the object. Object transforms default to 0.
		void load(const char*, 
				  glm::vec3 = glm::vec3(0,0,0), 
				  glm::vec3 = glm::vec3(0,0,0), 
				  glm::vec3 = glm::vec3(0,0,0));	 
		void compile();			// Link current object to OpenGL
		
		// Draws the object in its current state
		void draw(float, glm::mat4, glm::mat4, glm::mat4);

		void set_name(std::string);		// Set the name
		std::string get_name()const;	// Get the name
};
#endif
