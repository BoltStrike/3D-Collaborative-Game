#include "strValField.h"

StrValField::StrValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=Field::readString(f);
	printf("Done reading string value\n");
}
	
std::string StrValField::value(){
	return val;
}
char StrValField::typeLetter(){ 	 return 'S'; }
std::string StrValField::typeAbr(){ return "str"; }
std::string StrValField::typeFull(){return "string"; }
unsigned char StrValField::typeSize(){ return this->val.size(); }
unsigned char* StrValField::rawData(){ return (unsigned char*)this->val.c_str(); }

//function for writing data for StrValField
void StrValField::writeData(FILE* f){
	//write the name
	this->writeName(f);
	
	//write the data
	fputc('S',f);
	fputc('i',f);
	fputc((char)this->val.length(),f);
	//make sure the null charitor does not get printed
	fputs(this->val.c_str(),f);
}