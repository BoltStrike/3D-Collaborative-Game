#ifndef GRAPHICS_WRAPPER_FUNCTIONS_H
#define GRAPHICS_WRAPPER_FUNCTIONS_H

// Operating system dependent libraries
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <string>
#include <sstream>

#include "../../glad/glad.h"
#include "../../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"

#include "../../stb-master/stb_image.h"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include "../generic/program_log.h"

#include "input.h"

#include <unordered_map>

namespace gwf{

// unordered_map storing all windows of the program
static std::unordered_map<std::string, GLFWwindow*> windows;

void draw(unsigned int, unsigned int, unsigned int, unsigned int);
void use_shader(unsigned int);						// Use the given shader
void delete_shader(unsigned int);					// Delete given shader
void compile_shader(unsigned int&, const char*, const char*, const char*);
void create_texture(const char*, unsigned int&);	// Creates one texture
void delete_textures(unsigned int, unsigned int*);	// Delets given textures


void initialize_glfw();
void terminate_glfw();
bool load_opengl();

// Creates GLFW window with OpenGL context. Initializes OpenGL.
bool create_window(unsigned int, unsigned int, std::string);

void set_window(std::string);		// Sets the currently active window
void set_cursor(bool);				// Set mouse cursor visibility to Boolean
void set_vsync(bool);				// Sets the vsync property to given Boolean
void set_depth_test(bool);			// Sets depth testing to given Boolean
void set_backface_culling(bool);	// Sets backface culling to given Boolean
void set_blending(bool);			// Sets blending functionality to Boolean
void close();						// Closes the current window
bool should_close();				// Signifies if the render loop should stop
void swap_buffers();				// Swaps the OpenGL draw buffers
void get_dimensions(int&, int&);	// Retrieves screen dimensions

// Clears the window and sets it to color
void clear_viewport(float,float,float);	

// Callback functions
void framebuffer_size_callback(GLFWwindow*, int, int);

// Utility uniform functions provide access to shader variables
void setBool(unsigned int, const std::string&, bool);
void setInt(unsigned int, const std::string&, int);
void setFloat(unsigned int, const std::string&, float);
void setVec2(unsigned int, const std::string&, const glm::vec2&);
void setVec2(unsigned int, const std::string&, float, float);
void setVec3(unsigned int, const std::string&, const glm::vec3&);
void setVec3(unsigned int, const std::string&, float, float, float);
void setVec4(unsigned int, const std::string&, const glm::vec4&);
void setVec4(unsigned int, const std::string&, float, float, float, float);
void setMat2(unsigned int, const std::string&, const glm::mat2&);
void setMat3(unsigned int, const std::string&, const glm::mat3&);
void setMat4(unsigned int, const std::string&, const glm::mat4&);
// Utility function for checking shader compilation/linking errors.
void check_compile_errors(unsigned int, std::string);

}// Namespace gwf


#endif
