
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include "program_log.h"

class Json {
	private:
		std::ifstream input_file;
		char next;
		
		struct Value{
			std::string s;
			std::list<struct Value*> a;
			std::unordered_map<std::string, struct Value*> o;
		};

		struct Value values;

		std::string get_section (std::ifstream &, std::list<std::string> &);

		std::string to_string(struct Value);
		
		std::list<std::string> split_string (std::string, std::string);

		Value* get_value ();

		std::unordered_map<std::string, struct Value*> get_object ();
		void get_inner_object (std::unordered_map<std::string, struct Value*> &);

		std::list<struct Value*> get_array ();
		void get_inner_array (std::list<struct Value*> &);

		std::string get_num ();

		std::string get_string ();
		std::string get_inner_string ();

		bool next_nonwhitespace ();
	public:
		bool load(std::string, std::string = "");

		std::string get_string_representation();
};



#endif
