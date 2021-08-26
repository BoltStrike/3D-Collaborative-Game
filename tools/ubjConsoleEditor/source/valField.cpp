#include "valField.h"

ValField::ValField(int lineNum,std::string name):Field(lineNum,false,name){
	
}
std::string ValField::value(){ return "ERROR: No value, Default Class"; }
char ValField::typeLetter(){ return ' '; }
std::string ValField::typeAbr(){ return  "   "; }
std::string ValField::typeFull(){return  "     "; }