#ifndef UINT8_VAL_FEILD_H
#define UINT8_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class Uint8ValField:public ValField{
	private:
	uint8_t val;
	
	public:
	Uint8ValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
	virtual unsigned char typeSize();	//return number of bytes
	virtual unsigned char* rawData();	//return the bytes
};

#endif