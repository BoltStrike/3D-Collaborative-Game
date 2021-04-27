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

// If no vertex shader is given, this will be used
constexpr static const char* DEFAULT_VERTEX_SHADER = ""
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec2 aTexCoord;\n"
	"layout (location = 2) in vec3 aNormal;\n"
	"layout (location = 3) in vec3 aOffset;\n" // The position per instance
	"out vec2 TexCoord;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = projection * view * model * vec4(aPos+aOffset, 1.0f);\n"
	"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
	"}\n";

// If no fragment shader is given, this will be used
constexpr static const char* DEFAULT_FRAGMENT_SHADER = ""
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec2 TexCoord;\n"
	// texture samplers
	"uniform sampler2D texture1;\n"
	"uniform sampler2D texture2;\n"
	"void main()\n"
	"{\n"
	"	float result = mod(floor(TexCoord.x*10) + floor(TexCoord.y*10), 2.0);\n"
    "	FragColor = mix(vec4(1.0, 0.0, 1.0, 1.0), vec4(0.0, 0.0, 0.0, 1.0), result);\n"
	"}\n";
		
extern unsigned int *DEFAULT_SHADER_ID;	// Default shader, null on start


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
bool check_compile_errors(unsigned int, std::string);

}// Namespace gwf


#endif
