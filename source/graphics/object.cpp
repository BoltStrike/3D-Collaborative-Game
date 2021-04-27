
#include "object.h"

/******************************************************************************
 * This is the default constructor
******************************************************************************/
Object::Object () {
	mat = nullptr;
	mesh = nullptr;
	name = "Undefined";
	location = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	dilation = glm::vec3(0.0f, 0.0f, 0.0f);

	// REMOVE LATER ONCE INSTANCES HAVE BEEN ESTABLISHED IN THE SCENE
	num_instances = 100;
	translations = new glm::vec3[num_instances];
	for(unsigned int i = 0; i < num_instances; i++) {
		translations[i].x = 10 * i;
		translations[i].y = 10 * i;
		translations[i].z = 10 * i;
	}
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
Object::~Object () {
	std::string message = "  Deleting object: ";
	program_log(message.append(name).append("...\n"));
	
	delete mat;
	mat = nullptr;	
	delete mesh;
	mesh = nullptr;

	delete translations;
	translations = nullptr;

	message = "  Deleted object: ";
	program_log(message.append(name).append("\n"));
}

/******************************************************************************
 * This function loads the object specified by the given object file.
 * Params:
 *		filepath - Filepath from the executable to the object file
******************************************************************************/
void Object::load (const char *filepath, 
				   glm::vec3 new_location, 
				   glm::vec3 new_rotation, 
				   glm::vec3 new_dilation) {
	std::string message = "  Loading object: ";
	program_log(message.append(filepath).append("...\n"));

	location = new_location;
	rotation = new_rotation;
	dilation = new_dilation;
	
	std::string path;
	std::stringstream stream = file_tosstream(filepath);// Store file as stream
	stream >> path;
	if(path.compare("#") != 0) {	// Load material if one is provided
		mat = new Material(path.c_str());
		//mat->load(path.c_str());
	}
	stream >> path;
	if(path.compare("#") != 0) {	// Load mesh if one is provided
		mesh = new Mesh;
		mesh->load(path.c_str());
	}
	compile();

	message = "  Loaded object: ";
	program_log(message.append(filepath).append("\n"));
}

/******************************************************************************
 * This function prepares the object to be rendered with OpenGL. This should be
 * called every time either the material or the mesh changes.
******************************************************************************/
void Object::compile () {
	int posAttrib = glGetAttribLocation(mat->ID, "aPos");
	int texAttrib = glGetAttribLocation(mat->ID, "aTexCoord");
	int norAttrib = glGetAttribLocation(mat->ID, "aNormal");
	int offsetAttrib = glGetAttribLocation(mat->ID, "aOffset");

	mesh->compile(posAttrib, texAttrib, norAttrib);

	// Generate instance buffer
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * num_instances, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Enable instance buffer
	glEnableVertexAttribArray(offsetAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(offsetAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glVertexAttribDivisor(offsetAttrib, 1);  
	
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	gwf::use_shader(mat->ID);
	gwf::setInt(mat->ID, "texture1", 0);
	gwf::setInt(mat->ID, "texture2", 1);
}

/******************************************************************************
 * This function draws the object to the window. 
******************************************************************************/
void Object::draw (float time, 
				   glm::mat4 projection, 
				   glm::mat4 view, 
				   glm::mat4 model) {
	
	glBindVertexArray(mesh->VAO);// Set VAO as active vertex arrray
	
	gwf::use_shader(mat->ID);	// activate shader

	// Get maximum number of textures units available on this machine
	int max_textures;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_textures);
	
	// bind textures on corresponding texture units
	for(int i = 0; i < mat->num_textures && i < max_textures; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mat->tex[i]);
	}

	// model = glm::mat4
	model = glm::mat4(1.0f);
	
	glm::quat new_rot = glm::quat(rotation[0]==0?1.0:rotation[0], rotation[0], 0.0, 0.0);
	model = glm::toMat4(new_rot);
	//model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));// x
	//model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));// y
	//model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));// z
	model = glm::scale(model, dilation);
	model = glm::translate(model, location);

	gwf::setFloat(mat->ID, "time", time);
	gwf::setMat4(mat->ID, "projection", projection);
	gwf::setMat4(mat->ID, "view", view);
	gwf::setMat4(mat->ID, "model", model);

	// No instancing
	//glDrawArrays(GL_TRIANGLES, 0, mesh->get_num_faces() * 24);
	// With instancing
	glDrawArraysInstanced(GL_TRIANGLES, 0, mesh->get_num_faces() * 24, num_instances);  
}

/******************************************************************************
 * This function sets the name to the given name
******************************************************************************/
void Object::set_name (std::string new_name) {
	name = new_name;
}

/******************************************************************************
 * This function returns the current name
******************************************************************************/
std::string Object::get_name () const {
	return name;
}


