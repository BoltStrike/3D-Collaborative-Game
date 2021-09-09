#ifndef FEILD_H
#define FEILD_H

#include "globals.h"
#include <string>
#include <vector>
#include <stdio.h>

class Field{
	//fields
	protected:
	int lineNum;
	bool isObj;
	std::string name;
	
	public:
	//constructor
	Field(int,bool,std::string);
	Field(int*,std::string,FILE*);//for reading files
	
	//getters and setters
	int getLineNumber();
	void setLineNumber(int);
	bool getIsObj();
	void setIsObj(bool);
	std::string getName();
	void setName();
	
	//functions
	virtual std::vector<std::string> getText();
	
	//function empty must be implimented by child
	virtual void writeData(FILE*);
	void writeName(FILE*);
	static std::string readString(FILE* f){
		//get the length type
		fgetc(f);
		//get the string length
		int8_t len=fgetc(f);
		//printf("Str len: %d\n",len);
		char cStr[256];
		fgets(cStr,len+1,f);
		//printf("Got String: \"%s\"\n",cStr);
		return std::string(cStr);
	}
	static std::string readString(char type,FILE* f){
		//get the string length
		int8_t len=fgetc(f);
		//printf("Str len: %d\n",len);
		char cStr[256];
		fgets(cStr,len+1,f);
		//printf("Got String: \"%s\"\n",cStr);
		return std::string(cStr);
	}
	
};

#endif