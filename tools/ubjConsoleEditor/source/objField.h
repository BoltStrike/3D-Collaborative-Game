#ifndef OBJ_FEILD_H
#define OBJ_FEILD_H

#include "field.h"
#include "globals.h"
#include <string>
#include <vector>
#include "allValFields.h"

class ObjField: public Field{
	private:
	bool isExpanded;
	bool isArray;
	Field** fields;
	int numFields;
	
	public:
	//constructor
	ObjField(int,std::string,bool);	//for testing
	ObjField(int*,std::string,FILE*,bool);//for reading files
	~ObjField();
	
	//getter setters
	bool getIsExpanded();
	void setIsExpanded(bool);
	void expand();
	void contract();
	void toggelExpantion();
	Field* getField(int);
	Field* getFistField();
	Field* getLastField();
	int getNumFields();
	bool getIsArray();
	
	void writeData(FILE*);
	int readData(FILE*);
	
	//functions
	void addField(Field*);
	
	public:
		//search functions
		Field* findPrevious(int lineNumber);
		Field* findNext(int lineNumber);
	
};


#endif