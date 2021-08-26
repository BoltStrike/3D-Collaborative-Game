#ifndef STR_VAL_FEILD_H
#define STR_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class StrValField:public ValField{
	private:
	std::string val;
	
	public:
	StrValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
};

#endif