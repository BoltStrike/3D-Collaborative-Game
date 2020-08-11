/*****************************************************************************
** File: xml_tag.cpp
** Project: 3D Collaborative Game
** Date Created: 9 August 2020
** Description: Holds all the functions for the XMLTag class.
*****************************************************************************/

#include "xml_tag.h"

XMLTag::XMLTag () {
	name_length = 0;
	name = NULL;
	data_length = 0;
	data = NULL;
	closing = false;
}

XMLTag::XMLTag (char **new_name, unsigned int length) {
	set_name(new_name, length);
	data_length = 0;
	data = NULL;
	closing = false;
}

XMLTag::~XMLTag () {
	if (name != NULL) {
		delete [] name;
	}
	name = NULL;
}

void XMLTag::set_name(char **new_name, unsigned int length) {
	name_length = length;
	name = *new_name;
}

void XMLTag::set_data(char **new_data, unsigned int length) {
	data_length = length;
	data = *new_data;
}

void XMLTag::determine_closing () {	
	if (name[0] == '/' || name[name_length-2] == '/') {
		closing = true;
	}
}

void XMLTag::print () const {
	if (name != NULL) {
		std::cout << "string name: " << name << std::endl;
	}
	if (data != NULL) {
		std::cout << "data: " << data << std::endl;
	}
}

char* XMLTag::get_name () const {
	return name;
}

char* XMLTag::get_data () const {
	return data;
}
