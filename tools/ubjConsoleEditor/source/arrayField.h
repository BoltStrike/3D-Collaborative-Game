#ifndef ARRAY_FIELD_H
#define ARRAY_FIELD_H

class ArrayField:public Field{
	bool isExpanded;
	std::vector<Field*>* fields;
	
	public:
	//constructor
	ObjField(int,std::string);	//for testing
	ObjField(int*,std::string,FILE*);//for reading files
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
	
	void writeData(FILE*);
	int readData(FILE*);
	
	//functions
	void addField(Field*);
};

#endif