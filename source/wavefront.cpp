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
			num_verts += 3;
		}
		if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
			num_texture_coors += 2;
		}
		if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			num_normals += 3;
		}
		if (line[0] == 'f' && line[1] == ' ') {
			num_vertex_indices += 3;
			num_texture_indices += 3;
			num_normal_indices += 3;
		}
	}
	vert = new float[num_verts];
	texture_coors = new float[num_texture_coors];
	normals = new float[num_normals];
	
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
		if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
			std::istringstream iss(line);
			iss >> trash >> texture_coors[t*3] >> texture_coors[t*3+1] >> texture_coors[t*3+2];
			t++;
		}
		if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			std::istringstream iss(line);
			iss >> trash >> normals[n*3] >> normals[n*3+1] >> normals[n*3+2];
			n++;
		}
		else if (line[0] == 'f' && line[1] == ' ') {
			std::replace(line.begin(), line.end(), '/', ' ');
			std::istringstream iss(line);
			iss >> trash >> vertex_indices[i] >> texture_indices[i] >> normals_indices[i] >> vertex_indices[i+1] >> texture_indices[i+1] >> normals_indices[i+1] >> vertex_indices[i+2] >> texture_indices[i+2] >> normals_indices[i+2];
			i+=3;
			num_combined += 8*3;
		}
	}

	
	// File is 1 based, OpenGL is 0 based. -1 from indices to correct array
	for (int i = 0; i < num_vertex_indices; i++) {
		vertex_indices[i]--;
		texture_indices[i]--;
		normals_indices[i]--;
	}

	// Combine all vertex, texture, and normal data
	//num_combined = num_verts + num_texture_coors + num_normals;

	std::cout << num_verts << std::endl;
	std::cout << num_texture_coors << std::endl;
	std::cout << num_normals << std::endl;
	std::cout << num_combined << std::endl;
	
	combined = new float[num_combined];
	unsigned int vertex = 0;
	for (int i = 0; i < num_combined; i+=8) {
		combined[i] = vert[vertex_indices[vertex]*3];
		combined[i+1] = vert[vertex_indices[vertex]*3+1];
		combined[i+2] = vert[vertex_indices[vertex]*3+2];
		combined[i+3] = texture_coors[texture_indices[vertex]*2];
		combined[i+4] = texture_coors[texture_indices[vertex]*2+1];
		combined[i+5] = normals[normals_indices[vertex]*3];
		combined[i+6] = normals[normals_indices[vertex]*3+1];
		combined[i+7] = normals[normals_indices[vertex]*3+2];
		vertex++;
	}
	
	for (int i = 0; i < num_combined; i+=8) {
		std::cout << "V" << i/8 << ": ";
		std::cout << combined[i] << ", ";
		std::cout << combined[i+1] << ", ";
		std::cout << combined[i+2] << ", ";
		std::cout << combined[i+3] << ", ";
		std::cout << combined[i+4] << ", ";
		std::cout << combined[i+5] << ", ";
		std::cout << combined[i+6] << ", ";
		std::cout << combined[i+7];
		
		std::cout << std::endl;
	}
	
	num_combined_indices = num_combined/8;
	combined_indices = new unsigned int[num_combined_indices];
	for (int i = 0; i < num_combined_indices; i++) {
		combined_indices[i] = i;
	}
	
	//system("pause");

	// Combine all vertex, texture, and normal indices
	//num_combined_indices = num_vertex_indices + num_texture_indices + num_normal_indices;
	/*
	combined_indices = new unsigned int[num_combined_indices];
	for (int i = 0; i < num_vertex_indices; i++) {
		combined_indices[i] = vertex_indices[i];
	}
	for (int i = num_vertex_indices; i < num_texture_indices; i++) {
		combined_indices[i] = texture_indices[i];
	}
	for (int i = num_vertex_indices+num_texture_indices; i < num_vertex_indices; i++) {
		combined_indices[i] = normals_indices[i];
	}
	*/
	
	file.close();
	vertices = vert;
	return vert;
}
