#ifndef CHAR_VAL_FEILD_H
#define CHAR_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class CharValField:public ValField{
	private:
	char val;
	
	public:
	CharValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
	virtual unsigned char typeSize();	//return number of bytes
	virtual unsigned char* rawData();	//return the bytes
};

#endif