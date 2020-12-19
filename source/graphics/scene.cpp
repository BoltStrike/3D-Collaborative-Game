
#include "scene.h"

/******************************************************************************
 * This is the default constructor
******************************************************************************/
Scene::Scene () {
	objects = nullptr;
	num_objects = 0;
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
Scene::~Scene () {
	glDeleteVertexArrays(1, &VAO);
}

/******************************************************************************
 * This function loads the scene specified by the given scene file.
 * Params:
 * 		filepath - Filepath from the executable to the scene file
******************************************************************************/
void Scene::load (const char *filepath) {
	glGenVertexArrays(1, &VAO);	// Create a vertex array
	glBindVertexArray(VAO);		// Set the VAO as the active vertex array

	std::string path;	// Temporary string to store individual object paths
	std::stringstream stream = file_tosstream(filepath);// Read file
	stream >> num_objects;					// Get num_objects
	objects = new Object[num_objects];		// Allocate objects
	for(int i = 0; i < num_objects; i++) {	// Load objects
		stream >> path;
		objects[i].load(path.c_str());
	}
}

/******************************************************************************
 * This function draws the entire scene
******************************************************************************/
void Scene::draw () {
	for(unsigned int i = 0; i < num_objects; i++) {	// Draw each object
		// activate shader
		objects[i].mat->use();

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, objects[i].mat->tex[0]);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, objects[i].mat->tex[1]);

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(Window::fov), 
											    (float)Window::scr_width / 
											    (float)Window::scr_height, 
											    0.1f, 
											    100.0f);
		objects[i].mat->setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = glm::lookAt(Window::cameraPos, 
									 Window::cameraPos + Window::cameraFront, 
									 Window::cameraUp);
		objects[i].mat->setMat4("view", view);


		glBindVertexArray(VAO);	// Set the current vertex array to the VAO
		
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model = glm::translate(model, objects[i].get_position());
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		objects[i].mat->setMat4("model", model);
		
		glDrawArrays(GL_TRIANGLES, 0, objects[i].mesh->get_num_faces() * 24);
	}
}
