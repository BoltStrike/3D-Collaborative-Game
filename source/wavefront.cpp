/*****************************************************************************
** File: wavefront.cpp
** Project: 3D Collaborative Game
** Date Created: 10 August 2020
** Description: Holds all the functions for the Wavefront class
*****************************************************************************/

#include "wavefront.h"

Wavefront::Wavefront () {

}

Wavefront::~Wavefront () {
	
}


void Wavefront::print () const {
	for (int i = 0; i < num_verts; i += 3 ) {
		std::cout << "v\t" << vertices[i] << "\t" << vertices[i+1] << "\t" << vertices[i+2] << std::endl;
	}
	for (int i = 0; i < num_vertex_indices; i += 3) {
		std::cout << "f\t" << vertex_indices[i] << "\t" << vertex_indices[i+1] << "\t" << vertex_indices[i+2] << std::endl;
	}
}


float* Wavefront::get_vertices (const char *filepath) {
	float *vert;
	std::string trash;
	std::ifstream file(filepath);
	std::string line;
	while (!file.eof()) {
		std::getline(file, line);
		if (line[0] == 'v' && line[1] == ' ') {
			num_verts++;
		}
		if (line[0] == 'f' && line[1] == ' ') {
			num_vertex_indices += 3;
			num_texture_indices += 3;
			num_normal_indices += 3;
		}
	}
	num_verts *= 3;
	vert = new float[num_verts];
	vertex_indices = new unsigned int[num_vertex_indices];
	texture_indices = new unsigned int[num_texture_indices];
	normals_indices = new unsigned int[num_normal_indices];
	file.clear();
	file.seekg(0, file.beg);
	//std::cout << num_verts << std::endl;
	unsigned int v = 0;
	unsigned int t = 0;
	unsigned int n = 0;
	unsigned int i = 0;
	while (!file.eof()) {
		std::getline(file, line);
		if (line[0] == 'v' && line[1] == ' ') {
			std::istringstream iss(line);
			iss >> trash >> vert[v*3] >> vert[v*3+1] >> vert[v*3+2];
			v++;
		}
		else if (line[0] == 'f' && line[1] == ' ') {
			std::replace(line.begin(), line.end(), '/', ' ');
			std::istringstream iss(line);
			iss >> trash >> vertex_indices[i] >> texture_indices[i] >> normals_indices[i] >> vertex_indices[i+1] >> texture_indices[i+1] >> normals_indices[i+1] >> vertex_indices[i+2] >> texture_indices[i+2] >> normals_indices[i+2];
			i+=3;
		}
	}
	file.close();
	vertices = vert;
	return vert;
}
