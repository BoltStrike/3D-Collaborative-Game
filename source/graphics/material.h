
#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <sstream>

#include "../generic/program_log.h"
#include "../generic/file_tosstream.h"

#include "graphics_wrapper_functions.h"

class Material {
	private:
		const char *name;							// Name of material
		const char *v_source, *f_source, *g_source;	// Raw source code

		// If no vertex shader is given, this will be used
		constexpr static const char* DEFAULT_VERTEX_SHADER = ""
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec2 aTexCoord;\n"
			"layout (location = 2) in vec3 aNormal;\n"
			"out vec2 TexCoord;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
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
			"	FragColor = (1.0, 0.0, 1.0, 1.0);\n"	// magenta color
			"}\n";
		
	public:
		unsigned int ID;	// Shader ID
		unsigned int *tex;	// Texture IDs
		int num_textures;	// Quantity of textures
		
		Material();		// Default constructor
		~Material();	// Default destructor
		// Compiles shader program
		void create_shaders(const char*, const char*, const char*);
		void load(const char*);							// Loads material
};
#endif
