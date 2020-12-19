/*****************************************************************************
** File: wavefront.h
** Project: 3D Collaborative Game
** Date Created: 10 August 2020
** Description: Defines the Wavefront class for importing models
*****************************************************************************/

#ifndef WAVEFRONT_H
#define WAVEFRONT_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>

class Wavefront {
	private:
		float *vertices;
		
	public:
		float *texture_coors;
		float *normals;
		unsigned int num_verts;
		unsigned int num_texture_coors;
		unsigned int num_normals;

		float *combined;
		unsigned int num_combined;
		unsigned int *combined_indices;
		unsigned int num_combined_indices;
		
		unsigned int *vertex_indices;
		unsigned int *texture_indices;
		unsigned int *normals_indices;
		
		unsigned int num_vertex_indices;
		unsigned int num_texture_indices;
		unsigned int num_normal_indices;
		Wavefront();
		~Wavefront();
		void print()const;
		float* get_vertices(const char*);
};

#endif
