#ifndef F32_VAL_FEILD_H
#define F32_VAL_FEILD_H

#include "../valField.h"
#include <string.h>

class F32ValField:public ValField{
	private:
	float val;
	
	public:
	F32ValField(int,std::string,FILE*);
	
	public:
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
	virtual unsigned char typeSize();	//return number of bytes
	virtual unsigned char* rawData();	//return the bytes
};

#endif