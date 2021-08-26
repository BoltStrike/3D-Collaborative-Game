#ifndef VAL_FIELD_H
#define VAL_FIELD_H

#include "field.h"
#include <string.h>

class ValField:public Field{
	
	public:
	ValField(int,std::string);
	
	virtual std::string value();
	
	virtual char typeLetter();
	virtual std::string typeAbr();
	virtual std::string typeFull();
};


#endif