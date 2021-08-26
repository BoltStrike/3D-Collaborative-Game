#include "int8ValField.h"

Int8ValField::Int8ValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=fgetc(f);
}
	
std::string Int8ValField::value(){
	return std::to_string(val);
}
char Int8ValField::typeLetter(){ 	 return 'i'; }
std::string Int8ValField::typeAbr(){ return "i8 "; }
std::string Int8ValField::typeFull(){return "int8"; }