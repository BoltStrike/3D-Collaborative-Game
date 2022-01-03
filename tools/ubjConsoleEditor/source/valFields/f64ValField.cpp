#include "f64ValField.h"

F64ValField::F64ValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	char data[9];
	fgets(data,9,f);
	memcpy(&val,data,8);
}
	
std::string F64ValField::value(){
	return std::to_string(val);
}
char F64ValField::typeLetter(){ 	 return 'D'; }
std::string F64ValField::typeAbr(){ return "f64"; }
std::string F64ValField::typeFull(){return "float64"; }
unsigned char F64ValField::typeSize(){ return 8; }
unsigned char* F64ValField::rawData(){
	return reinterpret_cast<unsigned char*>(&this->val);
}