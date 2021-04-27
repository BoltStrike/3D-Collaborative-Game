/******************************************************************************
 * 		  File: graphics_engine.cpp
 * Description: This file contins all the functions of the graphics engine.
 *				all the functions are global and anonymous. 
******************************************************************************/

#include "graphics_wrapper_functions.h"

namespace gwf {

unsigned int *DEFAULT_SHADER_ID = nullptr;	// Default shader, null on start

void draw (unsigned int ID, unsigned int VAO, unsigned int num_vertices, unsigned int num_instances) {
	glBindVertexArray(VAO);// Set VAO as active vertex arrray
	glDrawArraysInstanced(GL_TRIANGLES, 0, num_vertices, num_instances);  
}

/******************************************************************************
 * This function activates the given shader for drawing.
 * Params:
 *		ID	- OpenGL ID referencing a shader program
 *****************************************************************************/
void use_shader (unsigned int ID) {
	glUseProgram(ID);
}

/******************************************************************************
 * This function deletes the given shader.
 * Params:
 *		ID	- OpenGL ID referencing a shader program
 *****************************************************************************/
void delete_shader (unsigned int ID) {
	glDeleteProgram(ID);
}

/******************************************************************************
 * This function compiles a shader program from a given set of shader source
 * files. The created program ID is returned by reference.
 * Params:
 *		ID	 - The OpenGL ID returned for the created program
 *	v_source - The vertex shader source code
 *	f_source - The fragment shader source code
 *	g_source - The geometry shader source code (may be nullptr)
 *****************************************************************************/
void compile_shader (unsigned int &ID, 
					 const char* v_source, 
					 const char* f_source, 
					 const char* g_source = nullptr) {
	if (DEFAULT_SHADER_ID == nullptr) {
		DEFAULT_SHADER_ID = new unsigned int;
		unsigned int temp_id;
		compile_shader(temp_id, DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);
		*DEFAULT_SHADER_ID = temp_id;
	}
	
	unsigned int v_id, f_id, g_id;	// OpenGL IDs

	// vertex shader
	v_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_id, 1, &v_source, NULL);
	glCompileShader(v_id);
	check_compile_errors(v_id, "VERTEX");

	// fragment Shader
	f_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_id, 1, &f_source, NULL);
	glCompileShader(f_id);
	check_compile_errors(f_id, "FRAGMENT");

	// geometry shader
	if(g_source != nullptr) {	// Only create geometry shader if provided with one
		g_id = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(g_id, 1, &g_source, NULL);
		glCompileShader(g_id);
		check_compile_errors(g_id, "GEOMETRY");
	}

	// Compile the shader program. Store its id in the ID variable
	ID = glCreateProgram();
	glAttachShader(ID, v_id);
	glAttachShader(ID, f_id);
	if (g_source != nullptr)
		glAttachShader(ID, g_id);
	glLinkProgram(ID);
	if (!check_compile_errors(ID, "PROGRAM"))
		ID = *DEFAULT_SHADER_ID;
	
	// delete shaders as they're linked into the program and no longer necessery
	glDeleteShader(v_id);
	glDeleteShader(f_id);
	if (g_source != nullptr)
		glDeleteShader(g_id);
		
}

/******************************************************************************
 * This function creates a single texture from an image ready for OpenGL. 
 * Params:
 *		filepath - Filepath from executable to the image
 *		tex		 - ID of the 
 *****************************************************************************/
void create_texture (const char *filepath, unsigned int &tex) {
	unsigned char *data;			// Holds image data from stbi
	int width, height, nrChannels;	// Variables used by stbi

	glGenTextures(1, &tex);				// Alocate texture ID in OpenGL
	glBindTexture(GL_TEXTURE_2D, tex);	// Specify ID refers to 2D texture
	
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Wrap x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// Wrap y
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// Zoom x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// Zoom y
	
	stbi_set_flip_vertically_on_load(true); // Flip image on y-axis
	// Load image with RGBA
	data = stbi_load(filepath, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data) {	// Check if anything was loaded.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
		
		glTexImage2D(	GL_TEXTURE_2D, 		// Generate the texture
						0, 
						GL_RGBA, 
						width, 
						height, 
						0, 
						GL_RGBA, 
						GL_UNSIGNED_BYTE, 
						data);
						
		glGenerateMipmap(GL_TEXTURE_2D);	// Generate the mipmap
		std::string message = "      Loaded image: ";
		program_log(message.append(filepath).append("\n").c_str());
	}
	else {
		std::string message = "      ERROR::Failed to load image: ";
		program_log(message.append(filepath).append("\n").c_str());
	}
	stbi_image_free(data);	// Texture linked to OpenGL. Data no longer needed.
}

/******************************************************************************
 * This function deletes a given set of textures.
 * Params:
 *		num_textures - Number of textures to delete
 *		tex		 	 - Pointer to array of textures to delete from
 *****************************************************************************/
void delete_textures (unsigned int num_textures, unsigned int* tex) {
	glDeleteTextures(num_textures, tex);
}

/******************************************************************************
 * This function creates a GLFW window with OpenGL context. By doing this,
 * OpenGL is loaded using GLAD. Returns true on success, false on failure.
 * Params:
 *		width	- The width of the window in pixels
 *		height	- The height of the window in pixels
 *		name	- The title of the window
******************************************************************************/
bool create_window (unsigned int width, unsigned int height, std::string name) {

	program_log("Creating window...\n");
	
	// glfw window creation
	//GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
	windows[name] = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (windows[name] == NULL)	{
		program_log("ERROR::Failed to create GLFW window\n");
		glfwTerminate();
		return false;
	}

	// Set the callback functions
	glfwSetFramebufferSizeCallback(windows[name], framebuffer_size_callback);
	glfwSetKeyCallback(windows[name], in::key_callback);
	glfwSetMouseButtonCallback(windows[name], in::mouse_button_callback);
	glfwSetCursorPosCallback(windows[name], in::mouse_callback);
	glfwSetScrollCallback(windows[name], in::scroll_callback);

	program_log("Created window\n");
	return true;
}

/******************************************************************************
 * This function loads GLFW libaries for OpenGL version 3.3. This does NOT
 * load OpenGL.
******************************************************************************/
void initialize_glfw () {
	// glfw: initialize and configure OpenGL v3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__	// Only for Mac OS
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

/******************************************************************************
 * This function unloads the GLFW libraries, closes all windows, and terminates
 * all GLFW functions.
******************************************************************************/
void terminate_glfw () {
	glfwTerminate();	// clear all allocated GLFW resources
}

/******************************************************************************
 * This function loads OpenGL 3.3 into the program using the GLAD loader. 
 * Returns true on success. 
******************************************************************************/
bool load_opengl () {	
	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		program_log("ERROR::Failed to initialize GLAD\n");
		return false;
	}
	else {
		return true;
	}	
}

/******************************************************************************
 * This function sets which window will be the current context. The provided
 * name is the title of the window.
******************************************************************************/
void set_window (std::string name) {
	glfwMakeContextCurrent(windows[name]);	// Get the window titled name
}

/******************************************************************************
 * This function sets the visiblity of the mouse cursor to the given Boolean.
******************************************************************************/
void set_cursor (bool state) {
	if (state) {
		// tell GLFW to show our mouse
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else {
		// tell GLFW to hide our mouse
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

/******************************************************************************
 * This function sets OpenGL depth testing to the given Boolean.
******************************************************************************/
void set_depth_test (bool state) {
	if (state) 
		glEnable(GL_DEPTH_TEST);	// Correct face layering
	else
		glDisable(GL_DEPTH_TEST);	// Don't correct face layering
}

/******************************************************************************
 * This function sets OpenGL backface culling to the given Boolean.
******************************************************************************/
void set_backface_culling (bool state) {
	if (state) {
		glEnable(GL_CULL_FACE);		// Backface culling
		glCullFace(GL_BACK);		// Cull the backs of faces
		glFrontFace(GL_CCW);  		// Set counter-clock-wise as the front face
	} 
	else {
		glDisable(GL_CULL_FACE);	// Disable backface culling
	}
}

/******************************************************************************
 * This function sets OpenGL blending functionality (transparency) to the 
 * given Boolean.
******************************************************************************/
void set_blending (bool state) {
	if (state) {
		glEnable(GL_BLEND);		// Enable blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 	// Add alpha channel
	}
	else {
		glDisable(GL_BLEND);	// Don't blend
	}
}

/******************************************************************************
 * This function enables v-sync on the window.
******************************************************************************/
void set_vsync (bool state) {
	if(state) { 
		glfwSwapInterval(1);	// Enable v-sync if state is true
		program_log("Set V-Sync: On\n");
	}
	else {
		glfwSwapInterval(0);	// Disable v-sync if state is false
		program_log("Set V-Sync: Off\n");
	}
}

/******************************************************************************
 * This function closes the currently active window.
******************************************************************************/
void close () {
	glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}

/******************************************************************************
 * This function signifies when the render loop should stop. It accomplishes
 * this by checking whether the GLFW window has been told to close.
******************************************************************************/
bool should_close () {
	return glfwWindowShouldClose(glfwGetCurrentContext());
}

/******************************************************************************
 * This function swaps the OpenGL buffers of the current window.
******************************************************************************/
void swap_buffers () {
	glfwSwapBuffers(glfwGetCurrentContext());	// Swap buffers
}

/******************************************************************************
 * This function retrieves the screen dimensions into the given integers.
******************************************************************************/
void get_dimensions (int &width, int &height) {
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
}

/******************************************************************************
 * This function clears the viewport to the given color.
******************************************************************************/
void clear_viewport (float red, float green, float blue) {
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/******************************************************************************
 * This function is the callback that adjusts the viewport whenever the 
 * window size changes. This ensure viewport matches the new window dimensions.
 * Width and height will be larger than specified on retina displays.
 * Params:
 *		window	- GLFWwindow being drawn to
 *		width	- New width of the window
 *		height	- New height of the window
******************************************************************************/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

/******************************************************************************
 * The 12 functions below are used to access the variables inside the 
 * shaders. All possible access types are included to provide the most 
 * flexability.
 * Params:
 *		name 	- The name of the variable being accessed
 *		value 	- The value the variable will be set to
 *		x		- The x component of the value the variable will be set to
 *		y		- The y component of the value the variable will be set to
 *		z		- The z component of the value the variable will be set to
 *		w		- The w component of the value the variable will be set to
 *		mat		- The matrix the variable will be set to
 *****************************************************************************/
void setBool(unsigned int ID, const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
/*****************************************************************************/
void setInt(unsigned int ID, const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
/*****************************************************************************/
void setFloat(unsigned int ID, const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
/*****************************************************************************/
void setVec2(unsigned int ID, const std::string& name, const glm::vec2& value) {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void setVec2(unsigned int ID, const std::string& name, float x, float y) {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
/*****************************************************************************/
void setVec3(unsigned int ID, const std::string& name, const glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void setVec3(unsigned int ID, const std::string& name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
/*****************************************************************************/
void setVec4(unsigned int ID, const std::string& name, const glm::vec4& value) {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void setVec4(unsigned int ID, const std::string& name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
/*****************************************************************************/
void setMat2(unsigned int ID, const std::string& name, const glm::mat2& mat) {
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
/*****************************************************************************/
void setMat3(unsigned int ID, const std::string& name, const glm::mat3& mat) {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
/*****************************************************************************/
void setMat4(unsigned int ID, const std::string& name, const glm::mat4& mat) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/******************************************************************************
 * This function checks for shader compilation/linking errors. 
 * Params:
 * 		shader 	- The ID of the shader that is being checked
 *		type	- A string describing the type of shader being checked
 *				  (Must be "VERTEX", "FRAGMENT", "GEOMETRY", or "PROGRAM")
 *****************************************************************************/
bool check_compile_errors(unsigned int shader, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::string message = "ERROR::SHADER_COMPILATION_ERROR of type: ";
			message.append(type).append("\n").append(infoLog);
			message.append("\n-------------------------------------------\n");
			program_log(message.c_str());
			return false;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::string message = "ERROR::SHADER_COMPILATION_ERROR of type: ";
			message.append(type).append("\n").append(infoLog);
			message.append("\n-------------------------------------------\n");
			program_log(message.c_str());
			return false;
		}
	}
	return true; // No errors
}

}// Namespace gwf

