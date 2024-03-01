
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
		//const char *v_source, *f_source, *g_source;	// Raw source code

		void load(const char*);				// Loads material from file
		void create_shaders(const char*, 	// Compiles shader program
							const char*, 	
							const char*);
	public:
		unsigned int ID;	// Shader ID
		unsigned int *tex;	// Texture IDs
		int num_textures;	// Quantity of textures
		
		Material(const char*);		// Default constructor
		~Material();	// Default destructor
		
};
#endif
