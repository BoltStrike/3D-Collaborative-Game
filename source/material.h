
#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <sstream>

#include "../glad/glad.h"
#include "../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"
#include "../stb-master/stb_image.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "program_log.h"
#include "file_tosstream.h"

class Material {
	private:
		const char *v_source, *f_source, *g_source;	// Raw source code
		unsigned int v_id, f_id, g_id;				// OpenGL IDs
		

		// If no vertex shader is given, this will be used
		constexpr static const char* DEFAULT_VERTEX_SHADER = ""
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec2 aTexCoord;\n"

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

		// Utility function for checking shader compilation/linking errors.
		void checkCompileErrors(GLuint, std::string);
		
	public:
		unsigned int ID;	// Shader ID
		unsigned int *tex;	// Texture IDs
		
		Material();
		// Compiles shader program
		void create_shaders(const char*, const char*, const char*);
		void load(const char*);							// Loads material
		void create_texture(const char*, unsigned int&);// Creates one texture
		void use();										// Activates shader
		
		// Utility uniform functions provide access to shader variables
		void setBool(const std::string&, bool) const;
		void setInt(const std::string&, int) const;
		void setFloat(const std::string&, float) const;
		void setVec2(const std::string&, const glm::vec2&) const;
		void setVec2(const std::string&, float, float) const;
		void setVec3(const std::string&, const glm::vec3&) const;
		void setVec3(const std::string&, float, float, float) const;
		void setVec4(const std::string&, const glm::vec4&) const;
		void setVec4(const std::string&, float, float, float, float);
		void setMat2(const std::string&, const glm::mat2&) const;
		void setMat3(const std::string&, const glm::mat3&) const;
		void setMat4(const std::string&, const glm::mat4&) const;
};
#endif
