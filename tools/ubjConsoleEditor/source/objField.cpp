#include "objField.h"

//constructor
ObjField::ObjField(int lineNumber,std::string name):Field(lineNumber,true,name){
	this->isExpanded=false;
	this->fields=new std::vector<Field*>();
}
ObjField::ObjField(int* lineNumber,std::string name,FILE* f):Field(*lineNumber,true,name){
	//start getting the feilds
	printf("In: ObjField::ObjField(int* lineNumber,std::string name,FILE* f)\n");
	char c=0;
	std::string currentName;
	this->isExpanded=false;
	lineNumber++;
	printf("Right before while loop\n");
	while((c=fgetc(f))!='}'){
		currentName=Field::readString(c,f);
		//switch based on the type
		switch(fgetc(f)){
			case '{':	//object
				this->addField((Field*) new ObjField(lineNumber,currentName,f));
				break;
			//add more cases
			case 'Z':	//null
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'N':	//no-op
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'T':	//true
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'F':	//false
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'i':	//int8
				this->addField((Field*) new Int8ValField(*lineNumber,currentName,f));
				break;
			case 'U':	//uint8
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'I':	//int16
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'l':	//int32
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'L':	//int64
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'd':	//float32
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'D':	//float64
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'H':	//high-percision number
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'C':	//char
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'S':	//string
				this->addField((Field*) new StrValField(*lineNumber,currentName,f));
				break;
			case '[':	//array
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case EOF :
				printf("ERROR: Unexpeced EOF");
			case '}':
				return;
			default:
				printf("ERROR: Unexpeced Charitor");
				return;
		}
		lineNumber++;
	}
}
ObjField::~ObjField(){
	delete this->fields;
}
	
//getter setters
bool ObjField::getIsExpanded(){ return this->isExpanded; }
void ObjField::setIsExpanded(bool isExpanded){ this->isExpanded=isExpanded; }
void ObjField::expand(){ this->isExpanded=true; }
void ObjField::contract(){ this->isExpanded=false; }
void ObjField::toggelExpantion(){ this->isExpanded=!isExpanded; }
Field* ObjField::getField(int pos){ return this->fields->at(pos); }
Field* ObjField::getFistField(){ return this->fields->front(); }
Field* ObjField::getLastField(){ return this->fields->back(); }
int ObjField::getNumFields(){ return this->fields->size(); }
	
void ObjField::writeData(FILE* f){
	//do obj header
	writeName(f);
	fputc('{',f);
	
	//do the data
	for(int i=0;i<this->fields->size();i++){
		this->fields->at(i)->writeData(f);
	}
	
	//do obj end
	fputc('}',f);
}

//functions
void ObjField::addField(Field* field){
	this->fields->push_back(field);
}
/*void ObjField::removeField(int pos){
	this->fields->erase(pos);
}*/