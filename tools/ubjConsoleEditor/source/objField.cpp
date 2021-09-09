#include "objField.h"

//constructor
ObjField::ObjField(int lineNumber,std::string name,bool isArray):Field(lineNumber,true,name){
	this->isExpanded=false;
	this->fields=NULL;
	this->numFields=0;
	this->isArray=isArray;
}
ObjField::ObjField(int* lineNumber,std::string name,FILE* f,bool isArray):Field(*lineNumber,true,name){
	this->fields=NULL;
	this->numFields=0;
	//start getting the feilds
	//printf("In: ObjField::ObjField(int* lineNumber,std::string name,FILE* f)\n");
	char c=0;
	char c2=0;
	std::string currentName="";
	this->isExpanded=true;//!isArray;
	this->isArray=isArray;
	(*lineNumber)++;
	//printf("Right before while loop\n");
	while(((c=fgetc(f))!='}'&&(!this->isArray)) || (c!=']'&&this->isArray)){
		//printf("in c=%c\n",c);
		if(!this->isArray)currentName=Field::readString(c,f);
		//printf("Reading: %s\n",currentName.c_str());
		//switch based on the type
		c2=this->isArray?c:fgetc(f);
		switch(c2){
			case '{':	//object
				this->addField((Field*) new ObjField(lineNumber,currentName,f,false));
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
				this->addField((Field*) new Uint8ValField(*lineNumber,currentName,f));
				break;
			case 'I':	//int16
				this->addField((Field*) new Int16ValField(*lineNumber,currentName,f));
				break;
			case 'l':	//int32
				this->addField((Field*) new Int32ValField(*lineNumber,currentName,f));
				break;
			case 'L':	//int64
				this->addField((Field*) new Int64ValField(*lineNumber,currentName,f));
				break;
			case 'd':	//float32
				this->addField((Field*) new F32ValField(*lineNumber,currentName,f));
				break;
			case 'D':	//float64
				this->addField((Field*) new F64ValField(*lineNumber,currentName,f));
				break;
			case 'H':	//high-percision number
				this->addField((Field*) new Field(lineNumber,currentName,f));
				break;
			case 'C':	//char
				this->addField((Field*) new CharValField(*lineNumber,currentName,f));
				break;
			case 'S':	//string
				this->addField((Field*) new StrValField(*lineNumber,currentName,f));
				break;
			case '[':	//array
				this->addField((Field*) new ObjField(lineNumber,currentName,f,true));
				break;
			case EOF :
				printf("ERROR: Unexpeced EOF");
				return;
			default:
				printf("ERROR: Unexpeced Charitor: %c\n",c2);
				return;
		}
		(*lineNumber)++;
		//printf("bot while\n");
	}
	//printf("out c=%c\n",c);
}
ObjField::~ObjField(){
	if(this->fields!=NULL){
		for(int a=0;a<this->numFields;a++) delete this->fields[a];
		delete this->fields;
	}
}
	
//getter setters
bool ObjField::getIsExpanded(){ return this->isExpanded; }
void ObjField::setIsExpanded(bool isExpanded){ this->isExpanded=isExpanded; }
void ObjField::expand(){ this->isExpanded=true; }
void ObjField::contract(){ this->isExpanded=false; }
void ObjField::toggelExpantion(){ this->isExpanded=!isExpanded; }
Field* ObjField::getField(int pos){ return this->fields[pos]; }
Field* ObjField::getFistField(){ return this->numFields?this->fields[0]:NULL; }
Field* ObjField::getLastField(){ return this->numFields?this->fields[this->numFields-1]:NULL; }
int ObjField::getNumFields(){ return this->numFields; }
bool ObjField::getIsArray(){ return this->isArray; }
	
void ObjField::writeData(FILE* f){
	//do obj header
	writeName(f);
	fputc('{',f);
	
	//do the data
	for(int i=0;i<this->numFields;i++){
		this->fields[i]->writeData(f);
	}
	
	//do obj end
	fputc('}',f);
}

//functions
void ObjField::addField(Field* field){
	//printf("adding field: %s\n",field->getName().c_str());
	//printf("old num: %d new num: %d\n",this->numFields,this->numFields+1);
	Field** newData=(Field**) malloc((this->numFields+1)*sizeof(Field*));
	if(newData==NULL){
		printf("ERROR: malloc failed at ObjField::addField(Field* field)");
		return;
	}
	//printf("malloc done\n");
	if(this->fields!=NULL){
		//printf("atempting memcpy\n");
		memcpy(newData,this->fields,this->numFields*sizeof(Field*));
		newData[this->numFields]=field;
		delete this->fields;
	}
	else newData[0]=field;
	//printf("coppy done\n");
	this->fields=newData;
	this->numFields++;
	//printf("done adding field: %s\n",field->getName().c_str());
}
/*void ObjField::removeField(int pos){
	this->fields->erase(pos);
}*/

//search functions
Field* ObjField::findPrevious(int lineNumber){
	if(this->getLineNumber()>lineNumber)return NULL;	//something has broke
	if(!this->isExpanded)return (Field*) this;
	//check the end first to save time on large items
	if(this->getLastField()->getLineNumber()<lineNumber)return this->getLastField();
	Field* closest=this;
	//go through the sub fields
	for(int i=0;i<this->numFields;i++){
		if(this->fields[i]->getLineNumber()<lineNumber){
			closest=this->fields[i];
			if(this->fields[i]->getIsObj()){
				closest=((ObjField*)this->fields[i])->findPrevious(lineNumber);
			}
		}
		else break;
	}
	return closest;
}
Field* ObjField::findNext(int lineNumber){
	if(this->getLineNumber()>lineNumber)return (Field*) this;
	if(!this->isExpanded)return (Field*) this;
	//check the end first to save time on large items
	if(this->getLastField()->getLineNumber()<lineNumber)return this->getLastField();
	Field* closest=this;
	Field* tmp=NULL;
	//go through the sub fields
	for(int i=0;i<this->numFields;i++){
		if(this->fields[i]->getLineNumber()<lineNumber){
			if(this->fields[i]->getIsObj()){
				closest=((ObjField*)this->fields[i])->findPrevious(lineNumber);
			}
		}
		else if(this->fields[i]->getLineNumber()>lineNumber)return this->fields[i];
	}
	return NULL; //if it gets here something is broke
}