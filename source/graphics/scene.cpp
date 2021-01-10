
#include "scene.h"

/******************************************************************************
 * This is the default constructor
******************************************************************************/
Scene::Scene () {
	name = "Unknown";
	objects = nullptr;
	num_objects = 0;
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
Scene::~Scene () {
	std::string message  = "Deleting scene: ";
	program_log(message.append(name).append("...\n"));
	
	delete [] objects;
	objects = nullptr;
	glDeleteVertexArrays(1, &VAO);
	
	message = "Deleted scene: ";
	program_log(message.append(name).append("\n"));
}

/******************************************************************************
 * This function loads the scene specified by the given scene file.
 * Params:
 * 		filepath - Filepath from the executable to the scene file
******************************************************************************/
void Scene::load (const char *filepath) {
	std::string message = "Loading scene: ";
	program_log(message.append(filepath).append("...\n"));

	std::string path;	// Temporary string to store individual object paths
	glm::vec3 location; // Temporary vector storing location
	glm::vec3 rotation; // Temporary vector storing rotation
	glm::vec3 dilation; // Temporary vector storing dilation
	
	std::stringstream stream = file_tosstream(filepath);// Read file
	stream >> num_objects;					// Get num_objects
	objects = new Object[num_objects];		// Allocate objects
	for(int i = 0; i < num_objects; i++) {	// Load objects
		stream >> path;

		stream >> location[0] >> location[1] >> location[2]; // Get location
		stream >> rotation[0] >> rotation[1] >> rotation[2]; // Get rotation
		stream >> dilation[0] >> dilation[1] >> dilation[2]; // Get dilation
		
		objects[i].load(path.c_str(), location, rotation, dilation);
	}

	message = "Loaded scene: ";
	program_log(message.append(filepath).append("...\n"));
}

/******************************************************************************
 * This function draws the entire scene
******************************************************************************/
void Scene::draw () {
	glBindVertexArray(VAO);	// Set the current vertex array to the VAO
	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(Window::fov), 
										    (float)Window::scr_width / 
										    (float)Window::scr_height, 
										    0.1f, 
										    100.0f);
	
	// camera/view transformation
	glm::mat4 view = glm::lookAt(Window::cameraPos, 
								 Window::cameraPos + Window::cameraFront, 
								 Window::cameraUp);
	// calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	
	for(int i = 0; i < num_objects; i++) {	// Draw each object
		//angle = 20.0 * i;
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		objects[i].draw(Window::lastFrame, projection, view, model);
	}
}
