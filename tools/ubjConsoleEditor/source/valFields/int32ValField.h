#ifndef INT32_VAL_FEILD_H
#define INT32_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class Int32ValField:public ValField{
	private:
	int32_t val;
	
	public:
	Int32ValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
	virtual unsigned char typeSize();	//return number of bytes
	virtual unsigned char* rawData();	//return the bytes
};

#endif