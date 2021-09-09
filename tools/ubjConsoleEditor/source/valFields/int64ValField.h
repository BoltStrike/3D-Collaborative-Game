#ifndef INT64_VAL_FEILD_H
#define INT64_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class Int64ValField:public ValField{
	private:
	int64_t val;
	
	public:
	Int64ValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
	virtual unsigned char typeSize();	//return number of bytes
	virtual unsigned char* rawData();	//return the bytes
};

#endif