
#include "material.h"

/******************************************************************************
 * This is the constructor
 * Params:
 *		filepath - Filepath from the executable to the material file
 *****************************************************************************/
Material::Material (const char *filepath) {
	name = "unkown";
	load(filepath);
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
Material::~Material () {
	std::string message = "    Deleting material: ";
	program_log(message.append(name).append("...\n"));

	gwf::delete_textures(num_textures, tex);
	gwf::delete_shader(ID);
	
	message = "    Deleted material: ";
	program_log(message.append(name).append("\n").c_str());
}

/******************************************************************************
 * This function loads the material from a material file.
 * Params:
 *		filepath - Filepath from the executable to the material file
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
		gwf::create_texture(tpath.c_str(), tex[i]);
	}

	message = "    Loaded material: ";
	program_log(message.append(filepath).append("\n"));
}

/******************************************************************************
 * This function compiles all the OpenGL sharder language files into a shader.
 * Params:
 * 		vpath - Filepath from executable to vertex sharder source 
 *		fpath - Filepath from executable to fragment sharder source 
 *		gpath - Filepath from executable to geometry shader source (optional)
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
		v_source = nullptr;
		program_log("ERROR::Could not find vertex shader. Default used.");
	}

	if(ffile.empty()) {	// Load default fragment shader if none provided
		f_source = nullptr; 
		program_log("ERROR::Could not find fragment shader. Default used.");
	}

	if(gfile.empty()) 	// Set to nullptr if no geometry shader provided
		g_source = nullptr;

	gwf::compile_shader(ID, v_source, f_source, g_source);
}



