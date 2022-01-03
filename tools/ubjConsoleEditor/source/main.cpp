#include <cstdio>
#include <iostream>

#include "field.h"
#include "objField.h"
#include "displayManager.h"
#include "console.h"
#include <vector>
#include <string>

//setup the globals
namespace Globals{
	
	int displayValueFieldType=2;
	int displayDecimalType=0;
	int displayFloatNumber=4;
	int displayDoubleNumber=6;
	bool displayLRWrap=false;
	bool displayUDWrap=false;
}

using namespace std;
ObjField* loadFile(std::string fileName);
string getInput();

int main(int argc, char** argv){
	std::string fileName="test_cube.ubj";
	ObjField* content=loadFile(fileName);//(Field*) new objField(0,"NULL");
	content->expand();
	ObjField* templates=new ObjField(1,"NULL",false);
	/*DisplayManager* dm=new DisplayManager(content,fileName,templates);
	dm->fullDisplayUpdate();
	dm->displayLoop();
	string in;
	int sleepCount=0;
	/*Console* console=new Console("Testing");
	console->setCursor(1,1);
	printf("Line 1\nLine 2\nLine 3\nLine 4\nLine 5\n");
	console->setCursor(1,1);
	console->deleteLines(1);
	console->setCursor(1,2);
	console->insertLineAbove(1);
	while(true){
		Sleep(500);
	}
	//char* in= new char[50];
	//cin>>in;*/
	FILE* fOut=fopen("testOutput.ubj","w");
	if(fOut==NULL){
		printf("Null file pointer");
		while(true){
			Sleep(500);
		}
	}
	content->writeData(fOut);
	fclose(fOut);
	delete content;
	printf("Done with everything");
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
	/*if(getc(f)!='{'){
		printf("ERROR in file: %s : missing '{' at start of file",fileName);
		printf("Please close this window");
	}*/
	printf("File oppened\n");
	//load the data in
	int lineNum=0;
	
	ObjField* r=new ObjField(&lineNum,"",f,false);
	fclose(f);
	return r;
	
}

/*string getInput(){
	//check if there is input to take in
	if(cin.peek()==EOF) return "";
	char c=cin.getc();
	char a;
	if(c==ESC){
		if(cin.peek()==EOF) return string(ESC);
		switch(cin.getc()){
			case '[':
				switch(cin.getc()){
					case 'A':
						return "Up";
						break;
					case 'B':
						return "Down";
						break;
					case 'C':
						return "Right";
						break;
					case 'D':
						return "Left";
						break;
					case 'H':
						return "Home";
						break;
					case 'F':
						return "End";
						break;
					case 'P':
						return "F1";
						break;
					case 'Q':
						return "F2";
						break;
					case 'R':
						return "F3";
						break;
					case 'S':
						return "F4";
						break;
					case '1':
						cin.getc();
						cin.getc();
						cin.getc();
				}
				break;
			case 'O':
				switch(cin.getc()){
					case 'A':
						return "Up";
						break;
					case 'B':
						return "Down";
						break;
					case 'C':
						return "Right";
						break;
					case 'D':
						return "Left";
						break;
					case '1':
						switch(cin.getc()){
							case '5':
								if(cin.getc()=='~')return "F5";
								break;
							case '7':
								if(cin.getc()=='~')return "F6";
								break;
							case '8':
								if(cin.getc()=='~')return "F7";
								break;
							case '9':
								if(cin.getc()=='~')return "F8";
								break;
						}
						return "";
						break;
					case '2':
						switch(cin.getc()){
							case '0':
								if(cin.getc()=='~')return "F9";
								break;
							case '1':
								if(cin.getc()=='~')return "F10";
								break;
							case '3':
								if(cin.getc()=='~')return "F11";
								break;
							case '4':
								if(cin.getc()=='~')return "F12";
								break;
							case '~':
								return "Insert";
								break;
						}
						return "";
						break;
					case '3':
						if(cin.getc()=='~')return "Delete";
						break;
					case '5':
						if(cin.getc()=='~')return "Page Up";
						break;
					case '6':
						if(cin.getc()=='~')return "Page Down";
						break;
				}
				break;
			default:
				return "Ctrl+"+cin.getc();
		}
	}else{
		return string(c);
	}
	
	
}*/