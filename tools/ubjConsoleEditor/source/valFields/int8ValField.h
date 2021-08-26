#ifndef INT8_VAL_FEILD_H
#define INT8_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class Int8ValField:public ValField{
	private:
	int8_t val;
	
	public:
	Int8ValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
};

#endif