/*****************************************************************************
** File: xml_object.h
** Project: 3D Collaborative Game
** Date Created: 7 August 2020
** Description: Defines the XMLObj class
*****************************************************************************/

#ifndef XML_OBJECT_H
#define XML_OBJECT_H

#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>

#include "xml_tag.h"

class XMLObj {
	private:
		char *file_location;
		char *source;
		unsigned int source_length;
		XMLTag *tags;
		char* load_file(const char*);
		void parse();
		unsigned int next_tag(unsigned int);
		void get_tag(XMLTag*, unsigned int);
		void get_data(XMLTag*, unsigned int);
		float* strings_to_floats(char*);
		float string_to_float(char*, unsigned int);
		
	public:
		XMLObj();
		XMLObj(const char*);
		~XMLObj();
		void load_source(const char*);
		float* get_vertices();
		
};

#endif
