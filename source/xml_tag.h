/*****************************************************************************
** File: xml_tag.h
** Project: 3D Collaborative Game
** Date Created: 7 August 2020
** Description: Defines the XMLTag class
*****************************************************************************/

#ifndef XML_TAG_H
#define XML_TAG_H

#include <cstring>
#include <iostream>

class XMLTag {
	private:
		
		unsigned int data_length;
		char *data;
		bool closing; 
	public: 
		unsigned int name_length;
		char *name;
		
		XMLTag();
		XMLTag(char**, unsigned int);
		~XMLTag();
		void set_name(char**, unsigned int);
		void set_data(char**, unsigned int);
		void determine_closing();
		void print()const;
		char* get_name()const;
		char* get_data()const;
};

#endif
