
#include "object.h"

/******************************************************************************
 * This is the default constructor
******************************************************************************/
Object::Object () {
	mat = nullptr;
	mesh = nullptr;
	name = "Undefined";
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(0.0f, 0.0f, 0.0f);
}

/******************************************************************************
 * This function loads the object specified by the given object file.
 * Params:
 *		filepath - Filepath from the executable to the object file
******************************************************************************/
void Object::load (const char *filepath) {
	std::string path;
	std::stringstream stream = file_tosstream(filepath);// Store file as stream
	stream >> path;
	if(path.compare("#") != 0) {	// Load material if one is provided
		mat = new Material;
		mat->load(path.c_str());
	}
	stream >> path;
	if(path.compare("#") != 0) {	// Load material if one is provided
		mesh = new Mesh;
		mesh->load(path.c_str());
	}
	compile();
}

/******************************************************************************
 * This function prepares the object to be rendered with OpenGL. This should be
 * called every time either the material or the mesh changes.
******************************************************************************/
void Object::compile () {
	GLint posAttrib = glGetAttribLocation(mat->ID, "aPos");
	GLint texAttrib = glGetAttribLocation(mat->ID, "aTexCoord");
	//glEnableClientState(GL_VERTEX_ARRAY);
	mesh->compile(posAttrib, texAttrib);
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	mat->use();
	mat->setInt("texture1", 0);
	mat->setInt("texture2", 1);
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
 * This function sets the position to the given position
******************************************************************************/
void Object::set_position (glm::vec3 new_position) {
	position = new_position;
}

/******************************************************************************
 * This function returns the current position
******************************************************************************/
glm::vec3 Object::get_position () const {
	return position;
}

/******************************************************************************
 * This function translates the position by the given vector
******************************************************************************/
void Object::translate (glm::vec3 movement) {
	position = position + movement;
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
 * This function sets the scale to the given scale
******************************************************************************/
void Object::set_scale (glm::vec3 new_scale) {
	scale = new_scale;
}

/******************************************************************************
 * This function returns the current scale
******************************************************************************/
glm::vec3 Object::get_scale () const {
	return scale;
}

/******************************************************************************
 * This function dilates the scale by the given vector
******************************************************************************/
void Object::dilate (glm::vec3 movement) {
	scale = scale + movement;
}
