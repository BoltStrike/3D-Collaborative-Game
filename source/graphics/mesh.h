
#ifndef MESH_H
#define MESH_H

#include <fstream>
#include <stdio.h>

#include "../../glad/glad.h"

#include "../generic/program_log.h"
#include "../generic/file_tosstream.h"

class Mesh {
	private:
		int name_length; 			// Length of the name string
		char* name;					// The name string
		float* coord, *normal, *uv;	// Vertex position, normal, and UV storage
		int* indices;				// Indicies to create faces
		float* vertex_data;			// OpenGL ready vertex data
		
		
		GLint posAttrib, texAttrib, norAttrib;	// Vertex attribute pointer IDs
		
		// Number of vertices, faces, and UV coordinates the object has
		int num_vertices, num_faces, num_uvs;
			
		// This struct defines the face struct. It holds indicies for the
		// position, normal, and UV arrays. All equal 0 by default;
		struct Face {
			float co[3][3] = {0}, nm[3][3] = {0}, uv[3][2] = {0};
		};
		struct Face* faces;	// holds copy of object data
		
		void prepare();	// Organizes object data in OpenGL ready format
		
	public:
		unsigned int VBO; 					// Vertex buffer ID for OpenGL
		unsigned int VAO;
	
		Mesh();								// Default constructor
		~Mesh();							// Default destructor
		void deallocate();					// Frees object data
		int get_name_length() const;		// Returns name_length
		char* get_name() const;				// Returns name char pointer
		int get_num_vertices() const;		// Returns num_vertices
		int get_num_faces() const;			// Returns num_faces
		struct Face get_face(int) const;	// Return face at given index
		float* get_vertex_data() const;		// Returns OpenGL ready data
		int load(const char*);				// Reads object data from file
		void compile(GLint, GLint, GLint);	// Link mesh to OpenGL
};
#endif
