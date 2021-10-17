
#ifndef VAL_FIELD_H
#define VAL_FIELD_H

#include "field.h"
#include <string.h>

class ValField:public Field{
	
	public:
	ValField(int,std::string);
	
	
	virtual std::string value();
	
	virtual char typeLetter();			//letter used for file stroage
	virtual std::string typeAbr();		//short constant length string
	virtual std::string typeFull();		//full c++ name
	virtual unsigned char typeSize();	//return number of bytes
	virtual unsigned char* rawData();	//return the bytes
	
	void writeData(FILE*);
	std::vector<std::string> getText();
};


#endif