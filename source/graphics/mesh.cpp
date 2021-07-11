
#include "mesh.h"
/******************************************************************************
 * This is the default constructor
 *****************************************************************************/
Mesh::Mesh () {
	num_vertices = 0;
	num_faces = 0;
	num_uvs = 0;
	
	coord = nullptr;
	normal = nullptr;
	uv = nullptr;
	indices = nullptr;
	vertex_data = nullptr;
	faces = nullptr;
}

/******************************************************************************
 * This is the destructor
 *****************************************************************************/
Mesh::~Mesh () {
	std::string message = "    Deleting mesh: ";
	program_log(message.append(name).append("...\n"));

	glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(texAttrib);
	glDisableVertexAttribArray(norAttrib);
	glDeleteBuffers(1, &VBO);
	
	deallocate();
	message = "    Deleted mesh: ";
	program_log(message.append(name).append("\n").c_str());
}

/******************************************************************************
 * This function deallocates the memory on the heap stored for the object.
 * This should only be called once all instances of the object have been
 * removed.
 *****************************************************************************/
void Mesh::deallocate () {
	delete faces;
	delete vertex_data;
	faces = nullptr;
	vertex_data = nullptr;
}

/******************************************************************************
 * This function returns a pointer to the string holding the name of the object
 *****************************************************************************/
std::string Mesh::get_name() const{
	return name;
}

/******************************************************************************
 * This function returns the number of vertices in the object
 *****************************************************************************/
int Mesh::get_num_vertices() const{
	return num_vertices;
}

/******************************************************************************
 * This function returns the number of faces in the object
 *****************************************************************************/
int Mesh::get_num_faces() const{
	return num_faces;
}

/******************************************************************************
 * This function returns the face at the given index. Returns a default face
 * if the index is outside the bounds of the faces array. The default face has
 * all values set to 0.
 * Params:
 * 		index - The index of the face in the faces array to return
 *****************************************************************************/
struct Mesh::Face Mesh::get_face(int index) const{
	if (index < num_faces && index >= 0) {
		return faces[index];
	}
	else {
		program_log("    ERROR::Index face out of bounds\n");
		struct Face default_face;
		return default_face;
	}
}

/******************************************************************************
 * This function returns a pointer to the vertex_data float array
 *****************************************************************************/
float* Mesh::get_vertex_data() const{
	return vertex_data;
}

/******************************************************************************
 * This function formats the mesh data in the coord, normal, and uv arrays
 * into the OpenGL ready vertex_data array and the faces array. After the
 * two arrays are filled with the data correctly, the coord, normal, and uv
 * arrays are deallocated.
 *****************************************************************************/
void Mesh::prepare () {
	if(vertex_data == nullptr) 					// Allocate only if not already
		vertex_data = new float[num_faces * 24];// (3+3+2)*3=24 floats per face

	//if(faces == nullptr)						// Allcoate only if not already
	//	faces = new struct Face[num_faces];		// Allocate a Face per face


	// Fill vertex_data as xyzXYZuv
	for(int i = 0; i < num_faces*3; i++) {
		vertex_data[i*8] = coord[indices[i]*3];			// position	
		vertex_data[i*8 + 1] = coord[indices[i]*3+1];
		vertex_data[i*8 + 2] = coord[indices[i]*3+2];

		vertex_data[i*8 + 3] = normal[indices[i]*3];	// normal	
		vertex_data[i*8 + 4] = normal[indices[i]*3+1];
		vertex_data[i*8 + 5] = normal[indices[i]*3+2];

		vertex_data[i*8 + 6] = uv[i*2];					// UVs	
		vertex_data[i*8 + 7] = uv[i*2+1];
	}

	/*
	// Fill faces
	for(int i = 0; i < num_faces; i++) {
		for(int j = 0; j < 3; j++) {	// Find values using indices array
			faces[i].co[j][0] = coord[(indices[i * 3 + j])*3];		// position	
			faces[i].co[j][1] = coord[(indices[i * 3 + j] + 1)*3];
			faces[i].co[j][2] = coord[(indices[i * 3 + j] + 2)*3];	
			
			faces[i].nm[j][0] = normal[indices[i * 3 + j + 1]];	// normals	
			faces[i].nm[j][1] = normal[indices[i * 3 + j + 1] + 1];	
			faces[i].nm[j][2] = normal[indices[i * 3 + j + 1] + 2];
		
			faces[i].uv[j][0] = uv[indices[i * 3 + j + 2]];		// UVs
			faces[i].uv[j][1] = uv[indices[i * 3 + j + 2] + 1];
		}
	}
	*/

	// Deallocated coord, normal, uv, and indices arrays. We are done with them
	delete coord;
	delete normal;
	delete uv;
	delete indices;
}

/******************************************************************************
 * This function loads all the data of an object file into the object. The file
 * it loads from must be formatted correctly otherwise the object loading will
 * be aborted or loaded incorrectly.
 * If the function is successful, it will return 0. Otherwise it will return
 * a negative integer corresponding to a particular error type.
 *
 * Params:
 * 		filepath - the relative filepath from the executable to the file
 *****************************************************************************/
int Mesh::load (const char* filepath) {
	std::string message = "    Loading mesh: ";
	program_log(message.append(filepath).append("...\n"));

	Ubj f;
	f.open(filepath);
	f = f.at("name");
	name = f.get_S();
	
	f = f.beginning().at("number of positions");
	num_vertices = f.get_l();
	f = f.beginning().at("positions");
	coord = new float[num_vertices * 3];		// Allocate position storage
	for(int i = 0; i < num_vertices * 3; i++)	// Store position data
		coord[i] = f.get_f();
	
	f = f.beginning().at("number of normals");
	num_normals = f.get_l();
	f = f.beginning().at("normals");
	normal = new float[num_normals * 3];		// Allocate position storage
	for(int i = 0; i < num_normals * 3; i++)	// Store position data
		normal[i] = f.get_f();
	
	f = f.beginning().at("number of uv coordinates");
	num_uvs = f.get_l();
	f = f.beginning().at("uv coordinates");
	uv = new float[num_uvs * 2];			// Allocate enough UV storage
	for(int i = 0; i < num_uvs * 2; i++)	// Store all UV coordinates
		uv[i] = f.get_f();
	
	f = f.beginning().at("number of faces");
	num_faces = f.get_l();
	f = f.beginning().at("indices");
	indices = new int[num_faces * 3];		// 3 vertex indices per face
	for(int i = 0; i < num_faces * 3; i++) 	// Store indices
		indices[i] = f.get_l();
	
	/*
	std::stringstream stream = file_tosstream(filepath);// Read file as stream
	
	stream >> name_length;					// Get the length of the name
	name = new char[name_length + 1]; 		// +1 for terminating char '\0'
	name[name_length] = '\0';				// Set terminating char
	for(int i = 0; i < name_length; i++)	// Store name
		stream.get(name[i]);
	
	stream >> num_vertices;	// Get the number of vertices
	
	coord = new float[num_vertices * 3];		// Allocate position storage
	for(int i = 0; i < num_vertices * 3; i++)	// Store position data
		stream >> coord[i];
	
	normal = new float[num_vertices * 3];		// Allocate normal storage
	for(int i = 0; i < num_vertices * 3; i++)	// Store normal data
		stream >> normal[i];
	
	stream >> num_uvs;						// Get the number of UV coordinates
	uv = new float[num_uvs * 2];			// Allocate enough UV storage
	for(int i = 0; i < num_uvs * 2; i++)	// Store all UV coordinates
		stream >> uv[i];

	stream >> num_faces;					// Get the number of faces
	indices = new int[num_faces * 3];		// 3 vertex indices per face
	for(int i = 0; i < num_faces * 3; i++) 	// Store indices
		stream >> indices[i];
	*/
	f.close();
	prepare();		// Fill faces and vertex_data
	
	
	
	message = "    Loaded mesh: ";
	program_log(message.append(filepath).append("\n").c_str());
	return 0;
}

/******************************************************************************
 * This function links the mesh to OpenGL. This should be called every time
 * the mesh changes
******************************************************************************/
void Mesh::compile(GLint pos, GLint tex, GLint nor) {
	posAttrib = pos;
	texAttrib = tex;
	norAttrib = nor;

	glGenVertexArrays(1, &VAO);	// Create a vertex array
	glBindVertexArray(VAO);		// Set the VAO as the active vertex array
	glGenBuffers(1, &VBO);		// Create a vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Set VBO as active vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 		// Link mesh to OpenGL
				 num_faces * 24 * sizeof(float), 
				 vertex_data, 
				 GL_STATIC_DRAW);

	// Specify the pointers to each of the types of vertex properties.
	// All properties must be in the same buffer but offset differently.
	// Each vertex has 3 floats for position, 3 floats for normals, and 2
	// floats for UV coordinates. The vertex float array is organized as
	// xyzXYZuv for the position, normal, and UV in that order.

	// Specify where in the vertex array the positions are
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// Specify where in the vertex array the UV coordinates are
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Specify where in the vertex array the normals are
	glEnableVertexAttribArray(norAttrib);
	glVertexAttribPointer(norAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
}
