
#ifndef UBJ_H
#define UBJ_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include "../generic/program_log.h"

class Ubj 
{
	private:
		std::fstream *f = nullptr;
		int pos = 0;
		char next;
		std::list<int> links;
		
		// Functions
		int search (std::string &);
		
		std::string get_name ();
		bool skip ();

	public:
		// Constructor
		Ubj();
		// Destructor
		~Ubj();
		
		// Navigation Functions
		bool open(std::string);
		void close();
		Ubj at(std::string);
		Ubj at(unsigned int);
		Ubj back();
		Ubj beginning();
		
		// Data Extraction Functions
		int8_t get_i ();
		uint8_t get_U ();
		int16_t get_I ();
		int32_t get_l ();
		int64_t get_L ();
		float get_f ();
		double get_d ();
		char get_C ();
		std::string get_S ();
};

#endif
