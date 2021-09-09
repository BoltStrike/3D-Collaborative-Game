#include "int64ValField.h"

Int64ValField::Int64ValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=(((uint64_t)fgetc(f))<<56) | (((uint64_t)fgetc(f))<<48) | (((uint64_t)fgetc(f))<<40) | (((uint64_t)fgetc(f))<<32) | (((uint64_t)fgetc(f))<<24) | (((uint64_t)fgetc(f))<<16) | (((uint64_t)fgetc(f))<<8) | ((uint64_t)fgetc(f));
}
	
std::string Int64ValField::value(){
	return std::to_string(val);
}
char Int64ValField::typeLetter(){ 	 return 'L'; }
std::string Int64ValField::typeAbr(){ return "i64"; }
std::string Int64ValField::typeFull(){return "int64"; }
unsigned char Int64ValField::typeSize(){ return 8; }
unsigned char* Int64ValField::rawData(){
	unsigned char* data=new unsigned char[8];
	if(data==NULL)return NULL;
	data[0]=(this->val>>56)&0x00000000000000FF;
	data[1]=(this->val>>48)&0x00000000000000FF;
	data[2]=(this->val>>40)&0x00000000000000FF;
	data[3]=(this->val>>32)&0x00000000000000FF;
	data[4]=(this->val>>24)&0x00000000000000FF;
	data[5]=(this->val>>16)&0x00000000000000FF;
	data[6]=(this->val>>8)&0x00000000000000FF;
	data[7]=this->val&0x00000000000000FF;
	return data;
}