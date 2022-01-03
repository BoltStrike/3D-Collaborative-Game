#include "f32ValField.h"

F32ValField::F32ValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	char data[5];
	fgets(data,5,f);
	memcpy(&val,data,4);
}
	
std::string F32ValField::value(){
	return std::to_string(val);
}
char F32ValField::typeLetter(){ 	 return 'd'; }
std::string F32ValField::typeAbr(){ return "f32"; }
std::string F32ValField::typeFull(){return "float32"; }
unsigned char F32ValField::typeSize(){ return 4; }
unsigned char* F32ValField::rawData(){
	return reinterpret_cast<unsigned char*>(&this->val);
}