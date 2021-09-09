#include "int16ValField.h"

Int16ValField::Int16ValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=(((uint16_t)fgetc(f))<<8) | ((uint16_t)fgetc(f));
}
	
std::string Int16ValField::value(){
	return std::to_string(val);
}
char Int16ValField::typeLetter(){ 	 return 'I'; }
std::string Int16ValField::typeAbr(){ return "i16"; }
std::string Int16ValField::typeFull(){return "int16"; }
unsigned char Int16ValField::typeSize(){ return 2; }
unsigned char* Int16ValField::rawData(){
	unsigned char* data=new unsigned char[2];
	if(data==NULL)return NULL;
	data[0]=(this->val>>8)&&0x00FF;
	data[1]=this->val&&0x00FF;
	return data;
}