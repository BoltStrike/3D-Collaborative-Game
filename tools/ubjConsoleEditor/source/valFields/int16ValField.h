#ifndef INT16_VAL_FEILD_H
#define INT16_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class Int16ValField:public ValField{
	private:
	int16_t val;
	
	public:
	Int16ValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
	virtual unsigned char typeSize();	//return number of bytes
	virtual unsigned char* rawData();	//return the bytes
};

#endif