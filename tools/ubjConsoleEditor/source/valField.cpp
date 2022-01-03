#include "valField.h"

ValField::ValField(int lineNum,std::string name):Field(lineNum,false,name){
	
}
std::string ValField::value(){ return "ERROR: No value, Default Class"; }
char ValField::typeLetter(){ return ' '; }
std::string ValField::typeAbr(){ return  "   "; }
std::string ValField::typeFull(){return  "     "; }
unsigned char ValField::typeSize(){ return 0; }
unsigned char* ValField::rawData(){ return NULL; }

//function for writing data for all valFeild types except string
void ValField::writeData(FILE* f){
	//write the name
	if(!this->name.empty())this->writeName(f);
	
	//write the data
	fputc(this->typeLetter(),f);
	unsigned char* data=this->rawData();
	for(int a=0;a<this->typeSize();a++){
		fputc(data[a],f);
	}
	char typesThatNeedFree[3]={'I','l','L'};//,'d','D'};
	for(int i=0;i<3;i++){
		if(this->typeLetter()==typesThatNeedFree[i])delete data;
	}
}

std::vector<std::string> ValField::getText(){
	std::vector<std::string> val;
	val.push_back(this->name);
	val.push_back(this->value());
	val.push_back(this->typeAbr());
	return val;
}