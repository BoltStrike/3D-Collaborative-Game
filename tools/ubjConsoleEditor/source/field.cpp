#include "field.h"

Field::Field(int lineNum,bool isObj,std::string name){
	this->lineNum=lineNum;
	this->isObj=isObj;
	this->name=name;
	//printf("Loaded line: %d name: %s\n",lineNum,name.c_str());
}
Field::Field(int* lineNum,std::string name,FILE* f){
	this->lineNum=*lineNum;
	this->isObj=false;
	this->name=name;
	//printf("Loaded line: %d name: %s\n",lineNum,name.c_str());
}

//getters and setters
int Field::getLineNumber(){ return this->lineNum; }
void Field::setLineNumber(int lineNum){ this->lineNum=lineNum; }
bool Field::getIsObj(){ return this->isObj; }
void Field::setIsObj(bool){ this->isObj=isObj; }
std::string Field::getName(){ return this->name; }
void Field::setName(){ this->name=name; }
//functions
std::vector<std::string> Field::getText(){
	std::vector<std::string> val;
	val.push_back(this->name);
	return val;
}
void Field::writeData(FILE* f){
	writeName(f);
	return;
}
void Field::writeName(FILE* f){
	fputc('i',f);
	fputc((char)this->name.length(),f);
	//make sure the null charitor does not get printed
	fputs(this->name.c_str(),f);
}