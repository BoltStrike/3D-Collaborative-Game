/*****************************************************************************
** File: xml_object.cpp
** Project: 3D Collaborative Game
** Date Created: 7 August 2020
** Description: Holds all the functions for the XMLObj class.
*****************************************************************************/


#include "xml_object.h"


XMLObj::XMLObj () {
	file_location = NULL;
}


XMLObj::XMLObj (const char *filepath) {
	file_location = NULL;
	load_source(filepath);
}



XMLObj::~XMLObj () {
	if (file_location != NULL) {
		delete [] file_location;
		file_location = NULL;
	}
}

char* XMLObj::load_file (const char *filepath) {
	std::ifstream file;
	char *data;
	
	file.open(filepath, std::ios::in | std::ios::binary);
	if (!file) {
		std::cout << "Failed to open \"" << filepath << "\"" << std::endl;
		return data;
	}
	
	file.seekg(0, std::ios::end);
	source_length = file.tellg();
	file.seekg(0, std::ios::beg);

	data = new char[source_length+1];
	data[source_length] = 0;

	unsigned long int i = 0;
	while (file.good()) {
		data[i] = file.get();
		if (!file.eof()) {
			i++;
		}
	}
	data[i] = 0;
	
	file.close();
	return data;
}


void XMLObj::load_source (const char *filepath) {
	unsigned int path_length = strlen(filepath);
	file_location = new char[path_length];
	strcpy(file_location, filepath);
	source = load_file(file_location);
	parse();
	
}


void XMLObj::parse () {
	unsigned int num_tags = 0;
	unsigned int index = 0;
	
	while (index < source_length)  {
		index = next_tag(index);
		num_tags++;
	}
	index = 1;
	tags = new XMLTag[num_tags];
	for (int i = 0; i < num_tags; i++) {
		get_tag(&tags[i], index);
		tags[i].determine_closing();
		tags[i].print();
		index = next_tag(index);
	}
}

unsigned int XMLObj::next_tag (unsigned int index) {
	index++;
	while (source[index] != '<') {
		index++;
	}
	return index;
}

void XMLObj::get_tag (XMLTag *tag, unsigned int start) {
	char *name;
	unsigned int length = 0;
	unsigned int index = start;
	index++;
	while (source[index] != '>') {
		length++;
		index++;
	}
	if (source[index] == '>' && source[index+1] != '\n' && index+1 < source_length) {
		get_data(tag, index+1);
	}
	index = start +1;
	length++;
	name = new char[length];
	for (int i = 0; i < length; i++) {
		name[i] = source[index+i];
	}
	name[length-1] = '\0';
	tag->set_name(&name, length);
}

void XMLObj::get_data (XMLTag *tag, unsigned int start) {
	char *data;
	unsigned int length = 0;
	unsigned int index = start;
	while (source[index] != '<') {
		length++;
		index++;
	}
	index = start;
	length++;
	data = new char[length];
	for (int i = 0; i < length; i++) {
		data[i] = source[index+i];
	}
	data[length-1] = '\0';
	tag->set_data(&data, length);
}

float* XMLObj::get_vertices () {
	const char *name = "float_array id=\"Cube-mesh-positions-array\" count=\"24\"";
	unsigned int length = 0;
	while (name[length] != '\0') {
		length++;
	}
	length++;
	unsigned int index = 0;

	while ( !(tags[index].name_length >= 8
			&& tags[index].name[0] == 'f'
			&& tags[index].name[1] == 'l'
			&& tags[index].name[2] == 'o'
			&& tags[index].name[3] == 'a'
			&& tags[index].name[4] == 't'
			&& tags[index].name[5] == '_'
			&& tags[index].name[6] == 'a'
			&& tags[index].name[7] == 'r')) {
		index++;
	}
	std::cout << index << std::endl;
	std::cout << tags[index].get_data() << std::endl;
	return strings_to_floats(tags[index].get_data());
}

float* XMLObj::strings_to_floats (char *string) {
	float *values;
	unsigned int length = strlen(string);
	unsigned int num_floats = 0;
	for (int i = 0; i < length; i++) {
		if (string[i] == ' ') {
			num_floats++;
		}
	}
	
	num_floats++;
	
	values = new float[num_floats];
	std::cout << "Num of floats: " << num_floats << std::endl;
	unsigned int index = 0;
	for (int i = 0; i < num_floats; i++) {
		values[i] = string_to_float(string, index);
		while (string[index] != ' ' && index < length) {
			index++;
		}
		index++;
		std::cout << values[i] << std::endl;
	}
	return values;
}


float XMLObj::string_to_float (char *string, unsigned int start) {
	float value = 0.0f;
	bool negative = false;
	unsigned int dot_placement = 0;
	unsigned int length = 0;
	unsigned int index = start;
	while (string[index] != ' ') {
		length++;
		index++;
	}
	for (int i = 0; i < length; i++) {
		if (string[0] == '-') {
			negative  = true;
			continue;
		}
		if (string[i] == '.') {
			dot_placement = i;
		}
		value += (string[i]-48)*pow(10, length-i-1);
	}
	value = value / pow(10, dot_placement);
	if (negative) {
		value = value * -1.0f;
	}
	return value;
}




