
#include "material.h"

/******************************************************************************
 * This is the default constructor
 *****************************************************************************/
Material::Material () {
	name = "unkown";
	v_source = nullptr;
	f_source = nullptr;
	g_source = nullptr;
	v_id = 0;
	f_id = 0;
	g_id = 0;
	ID = 0;
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
Material::~Material () {
	std::string message = "    Deleting material: ";
	program_log(message.append(name).append("...\n"));

	glDeleteTextures(num_textures, tex);
	glDeleteProgram(ID);
	
	message = "    Deleted material: ";
	program_log(message.append(name).append("\n").c_str());
}

/******************************************************************************
 * This function loads the material from a material file.
 * Params:
 *		filepath - Filepath from the exacutable to the material file
 *****************************************************************************/
void Material::load (const char *filepath) {
	std::string message = "    Loading material: ";
	program_log(message.append(filepath).append("...\n").c_str());

	num_textures = 0;		// Stores number of textures material uses
	std::string vpath;		// Stores path to vertex shader source
	std::string fpath;		// Stores path to fragment shader source
	std::string gpath;		// Stores path to geometry shader source
	std::string tpath;		// Stores path to current texture being loaded

	std::stringstream stream = file_tosstream(filepath);// Read material file
	stream >> vpath;	// Get path to vertex shader source
	stream >> fpath;	// Get path to fragment shader source
	stream >> gpath;	// Get path to geometry shader source (may be empty)

	// Create shaders. Use geometry if provided with it. (# signifies no geo)
	if(gpath.compare("#") == 0)	
		create_shaders(vpath.c_str(), fpath.c_str(), nullptr);
	else
		create_shaders(vpath.c_str(), fpath.c_str(), gpath.c_str());
	
	stream >> num_textures;	// Get number of textures used by material
	if (num_textures > 0)
		tex = new unsigned int[num_textures];	// Allocate IDs for textures
	for(int i = 0; i < num_textures; i++) {		// Create each texture
		stream >> tpath;
		create_texture(tpath.c_str(), tex[i]);
	}

	message = "    Loaded material: ";
	program_log(message.append(filepath).append("\n").c_str());
}

/******************************************************************************
 * This function compiles all the OpenGL sharder language files into a shader.
 * Params:
 * 		vpath - Filepath from exacutable to vertex sharder source 
 *		fpath - Filepath from exacutable to fragment sharder source 
 *		gpath - Filepath from exacutable to geometry shader source (optional)
 *****************************************************************************/
void Material::create_shaders (	const char* vpath = nullptr, 
								const char* fpath = nullptr, 
								const char* gpath = nullptr) {
	// Temporary strings
	std::string vfile;
	std::string ffile;
	std::string gfile;

	if(vpath != nullptr) // Attempt to load vertex shader
		vfile = file_tosstream(vpath).str();

	if(fpath != nullptr) // Attempt to load fragment shader
		ffile = file_tosstream(fpath).str();

	if(gpath != nullptr) // Attempt to load geometry shader
		gfile = file_tosstream(gpath).str();

	v_source = vfile.c_str();
	f_source = ffile.c_str();
	g_source = gfile.c_str();

	if(vfile.empty()) {	// Load default vertex shader if none provided
		v_source = DEFAULT_VERTEX_SHADER;
		program_log("ERROR::Could not find vertex shader. Default used.");
	}

	if(ffile.empty()) {	// Load default fragment shader if none provided
		f_source = DEFAULT_FRAGMENT_SHADER; 
		program_log("ERROR::Could not find fragment shader. Default used.");
	}

	if(gfile.empty()) 	// Set to nullptr if no geometry shader provided
		g_source = nullptr;

	// vertex shader
	v_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_id, 1, &v_source, NULL);
	glCompileShader(v_id);
	checkCompileErrors(v_id, "VERTEX");

	// fragment Shader
	f_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_id, 1, &f_source, NULL);
	glCompileShader(f_id);
	checkCompileErrors(f_id, "FRAGMENT");

	// geometry shader
	if(gpath != nullptr) {	// Only create geometry shader if provided with one
		g_id = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(g_id, 1, &g_source, NULL);
		glCompileShader(g_id);
		checkCompileErrors(g_id, "GEOMETRY");
	}

	// Compile the shader program. Store its id in the ID variable
	ID = glCreateProgram();
	glAttachShader(ID, v_id);
	glAttachShader(ID, f_id);
	if (gpath != nullptr)
		glAttachShader(ID, g_id);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	
	// delete shaders as they're linked into the program and no longer necessery
	glDeleteShader(v_id);
	glDeleteShader(f_id);
	if (gpath != nullptr)
		glDeleteShader(g_id);
}

/******************************************************************************
 * This function creates a single texture from an image ready for OpenGL.
 * Params:
 *		filepath - Filepath from executable to the image
 *		tex		 - ID of the 
 *****************************************************************************/
void Material::create_texture (const char *filepath, unsigned int &tex) {
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
 * This function activates the current shader for drawing.
 *****************************************************************************/
void Material::use() {
	glUseProgram(ID);
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
void Material::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
/*****************************************************************************/
void Material::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
/*****************************************************************************/
void Material::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
/*****************************************************************************/
void Material::setVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Material::setVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
/*****************************************************************************/
void Material::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Material::setVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
/*****************************************************************************/
void Material::setVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Material::setVec4(const std::string& name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
/*****************************************************************************/
void Material::setMat2(const std::string& name, const glm::mat2& mat) const {
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
/*****************************************************************************/
void Material::setMat3(const std::string& name, const glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
/*****************************************************************************/
void Material::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


/******************************************************************************
 * This function checks for shader compilation/linking errors. This function
 * is only used internally within the Material class.
 * Params:
 * 		shader 	- The ID of the shader that is being checked
 *		type	- A string describing the type of shader being checked
 *				  (Must be "VERTEX", "FRAGMENT", "GEOMETRY", or "PROGRAM")
 *****************************************************************************/
void Material::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::string message = "ERROR::SHADER_COMPILATION_ERROR of type: ";
			message.append(type);
			message.append("\n");
			message.append(infoLog);
			message.append("\n-------------------------------------------\n");
			program_log(message.c_str());
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
			message.append(type);
			message.append("\n");
			message.append(infoLog);
			message.append("\n-------------------------------------------\n");
			program_log(message.c_str());
		}
	}
}
