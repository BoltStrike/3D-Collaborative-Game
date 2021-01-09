
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
		mat = new Material;
		mat->load(path.c_str());
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
	GLint posAttrib = glGetAttribLocation(mat->ID, "aPos");
	GLint texAttrib = glGetAttribLocation(mat->ID, "aTexCoord");
	GLint norAttrib = glGetAttribLocation(mat->ID, "aNormal");

	mesh->compile(posAttrib, texAttrib, norAttrib);
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	mat->use();
	mat->setInt("texture1", 0);
	mat->setInt("texture2", 1);
}

/******************************************************************************
 * This function draws the object to the window. 
******************************************************************************/
void Object::draw (float time, 
				   glm::mat4 projection, 
				   glm::mat4 view, 
				   glm::mat4 model) {
	
	glBindVertexArray(mesh->VAO);// Set VAO as active vertex arrray
	
	mat->use();// activate shader

	// Get maximum number of textures units available on this machine
	int max_textures;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_textures);
	
	// bind textures on corresponding texture units
	for(int i = 0; i < mat->num_textures && i < max_textures; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mat->tex[i]);
	}

	model = glm::translate(model, location);
	model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, dilation);

	mat->setFloat("time", time);
	mat->setMat4("projection", projection);
	mat->setMat4("view", view);
	mat->setMat4("model", model);
	
	glDrawArrays(GL_TRIANGLES, 0, mesh->get_num_faces() * 24);
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

/******************************************************************************
 * This function sets the location to the given location
******************************************************************************/
void Object::set_location (glm::vec3 new_location) {
	location = new_location;
}

/******************************************************************************
 * This function returns the current location
******************************************************************************/
glm::vec3 Object::get_location () const {
	return location;
}

/******************************************************************************
 * This function translates the location by the given vector
******************************************************************************/
void Object::translate (glm::vec3 movement) {
	location = location + movement;
}

/******************************************************************************
 * This function sets the rotation to the given rotation
******************************************************************************/
void Object::set_rotation (glm::vec3 new_rotation) {
	rotation = new_rotation;
}

/******************************************************************************
 * This function returns the current rotation
******************************************************************************/
glm::vec3 Object::get_rotation () const {
	return rotation;
}

/******************************************************************************
 * This function rotates the rotation by the given vector
******************************************************************************/
void Object::rotate (glm::vec3 movement) {
	rotation = rotation + movement;
}

/******************************************************************************
 * This function sets the dilation to the given dilation
******************************************************************************/
void Object::set_dilation (glm::vec3 new_dilation) {
	dilation = new_dilation;
}

/******************************************************************************
 * This function returns the current dilation
******************************************************************************/
glm::vec3 Object::get_dilation () const {
	return dilation;
}

/******************************************************************************
 * This function dilates the dilation by the given vector
******************************************************************************/
void Object::dilate (glm::vec3 movement) {
	dilation = dilation + movement;
}
