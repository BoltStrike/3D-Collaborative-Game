#include <cstdio>
#include <iostream>

#include "field.h"
#include "objField.h"
#include "displayManager.h"
#include <vector>
#include <string>

//setup the globals
namespace Globals{
	
	int displayValueFieldType=2;
	int displayDecimalType=0;
	int displayFloatNumber=4;
	int displayDoubleNumber=6;
	
}

using namespace std;
ObjField* loadFile(std::string fileName);

int main(int argc, char** argv){
	std::string fileName="testFile1.txt";
	ObjField* content=loadFile(fileName);//(Field*) new objField(0,"NULL");
	content->expand();
	/*content->addField((Field*) new ObjField(1,"Obj 1"));
	content->addField((Field*) new ObjField(4,"Obj 2"));
	content->addField((Field*) new ObjField(5,"Obj 3"));
	content->addField((Field*) new ObjField(6,"Obj 4"));
	content->addField((Field*) new ObjField(9,"Obj 5"));
	content->addField((Field*) new ObjField(10,"Obj 6"));
	content->addField((Field*) new ObjField(11,"Obj 7"));
	content->addField((Field*) new ObjField(12,"Obj 8"));
	content->addField((Field*) new ObjField(13,"Obj 9"));
	//printf("size: %d%s\n",fields->size(),fields->at(2).getName().c_str());
	//add some lower objects
	((ObjField*)fields->getField(0))->expand();
	((ObjField*)fields->getField(0))->addField((Field*) new ObjField(2,"Obj 1-1"));
	((ObjField*)fields->getField(0))->addField((Field*) new ObjField(3,"Obj 1-2"));
	((ObjField*)fields->getField(3))->expand();
	((ObjField*)fields->getField(3))->addField((Field*) new ObjField(7,"Obj 4-1"));
	((ObjField*)fields->getField(3))->addField((Field*) new ObjField(8,"Obj 4-2"));*/
	
	DisplayManager* dm=new DisplayManager(content,fileName);
	dm->updateDisplay();
	char* in= new char[50];
	cin>>in;
	delete in;
	delete content;
	return 0;
}

ObjField* loadFile(std::string fileName){
	//open the file
	FILE* f=fopen(fileName.c_str(),"r");
	//check if file opened
	if(f==NULL){
		printf("ERROR opening file: %s",fileName);
		printf("Please close this window");
	}
	//read the first chritor
	if(getc(f)!='{'){
		printf("ERROR in file: %s : missing '{' at start of file",fileName);
		printf("Please close this window");
	}
	printf("File oppened\n");
	//load the data in
	int lineNum=0;
	return new ObjField(&lineNum,"NULL",f);
	
	
	
}