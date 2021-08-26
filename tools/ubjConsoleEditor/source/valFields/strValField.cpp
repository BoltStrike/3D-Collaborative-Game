#include "strValField.h"

StrValField::StrValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=Field::readString(f);
}
	
std::string StrValField::value(){
	return val;
}
char StrValField::typeLetter(){ 	 return 'S'; }
std::string StrValField::typeAbr(){ return "str"; }
std::string StrValField::typeFull(){return "string"; }