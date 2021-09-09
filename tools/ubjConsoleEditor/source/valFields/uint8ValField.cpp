#include "uint8ValField.h"

Uint8ValField::Uint8ValField(int lineNum,std::string name,FILE* f):ValField(lineNum,name){
	this->val=fgetc(f);
}
	
std::string Uint8ValField::value(){
	return std::to_string(val);
}
char Uint8ValField::typeLetter(){ 	 return 'U'; }
std::string Uint8ValField::typeAbr(){ return "ui8"; }
std::string Uint8ValField::typeFull(){return "uint8"; }
unsigned char Uint8ValField::typeSize(){ return 1; }
unsigned char* Uint8ValField::rawData(){ return (unsigned char*)&val; }