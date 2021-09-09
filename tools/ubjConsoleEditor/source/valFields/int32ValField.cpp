#include "int32ValField.h"

Int32ValField::Int32ValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=(((uint32_t)fgetc(f))<<24) | (((uint32_t)fgetc(f))<<16) | (((uint32_t)fgetc(f))<<8) | ((uint32_t)fgetc(f));
}
	
std::string Int32ValField::value(){
	return std::to_string(val);
}
char Int32ValField::typeLetter(){ 	 return 'l'; }
std::string Int32ValField::typeAbr(){ return "i32"; }
std::string Int32ValField::typeFull(){return "int32"; }
unsigned char Int32ValField::typeSize(){ return 4; }
unsigned char* Int32ValField::rawData(){
	unsigned char* data=new unsigned char[4];
	if(data==NULL)return NULL;
	data[0]=(this->val>>24)&0x000000FF;
	data[1]=(this->val>>16)&0x000000FF;
	data[2]=(this->val>>8)&0x000000FF;
	data[3]=this->val&0x000000FF;
	return data;
}