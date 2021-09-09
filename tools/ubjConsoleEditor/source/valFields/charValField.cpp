#include "charValField.h"

CharValField::CharValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=fgetc(f);
}
	
std::string CharValField::value(){
	return std::string(1,val);
}
char CharValField::typeLetter(){ 	 return 'C'; }
std::string CharValField::typeAbr(){ return "chr"; }
std::string CharValField::typeFull(){return "char"; }
unsigned char CharValField::typeSize(){ return 1; }
unsigned char* CharValField::rawData(){ return (unsigned char*)&val; }