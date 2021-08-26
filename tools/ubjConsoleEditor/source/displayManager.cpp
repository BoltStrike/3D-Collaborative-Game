#include "displayManager.h"

//constructor
DisplayManager::DisplayManager(ObjField* fields,std::string fileName){
	if(!EnableVTMode()){
		printf("Boot Failed");
	}
	//set window name
	printf(OSI "2; %s - UBJ Console Editor\x07",fileName.c_str());
	
	//set size
	//132 coulmbs
	//printf(CSI "?3h");
	
	//set scrolling margin
	//will have top menue as that is easer right now
	//printf(CSI "5;r");
	/*for(int i=0;i<50;i++){
		printf("Line %d\n",i);
		Sleep(10);
	}*/
	
	//printf("This is an " CSI "4mUnderline" CSI "24m No Underline\n");
	this->fields=fields;
	updateScreenSize();
	printf("\nnumRows: %d\nnumCols: %d\n",numRows,numCols);
	this->currentRowNum=5;
}
	
//getters and setters
void DisplayManager::setCurrentLineNum(int val){ this->currentLineNum=val; }
int DisplayManager::getCurrentLineNum(){ return this->currentLineNum; }
void DisplayManager::setCurrentRowNum(int val){ this->currentRowNum=val; }
int DisplayManager::getCurrentRowNum(){ return this->currentRowNum; }
void DisplayManager::setCurrentColNum(int val){ this->currentColNum=val; }
int DisplayManager::getCurrentColNum(){ return this->currentColNum; }

//alt setters
void DisplayManager::cursorUp(){ this->currentLineNum++; }
void DisplayManager::cursorDown(){ this->currentLineNum--; }
void DisplayManager::cursorLeft(){ this->currentColNum--; }
void DisplayManager::cursorRight(){ this->currentColNum++; }


//display functions
void DisplayManager::updateDisplay(){
	//erase screen
	printf(CSI "2J");
	//disregaurding top/bottom bar
	//heep cursor at top for now
	printf(CSI "0;0H");
	int numLinesLeft=numRows;
	for(int i=0;(i<this->fields->getNumFields())&&numLinesLeft>0;i++){
		if(this->fields->getField(i)->getIsObj()){
			//start the recurrsion
			numLinesLeft=displayObj((ObjField*)this->fields->getField(i),numLinesLeft,1);
		}else{
			//just a field
			printLineNumAndTabs(this->fields->getField(i)->getLineNumber(),0);
			for(std::string s: this->fields->getField(i)->getText()){
				printf(" %s",s.c_str());
			}
			printf("\n");
			numLinesLeft--;
		}
	}
	
}

int DisplayManager::displayObj(ObjField* obj,int numLinesLeft,int numTabs){
	if(numLinesLeft<=0)return 0;
	//charck if the Obj is expanded or not
	if(obj->getIsExpanded()){
		//all sub fields need to be printed
		printLineNumAndTabs(obj->getLineNumber(),numTabs);
		printf(" " NEGATIVE_MINUS " %s" "\n",obj->getName().c_str());
		numTabs++;
		numLinesLeft--;
		//now go through the fields
		for(int i=0;i<obj->getNumFields() && numLinesLeft>0;i++){
			if(obj->getField(i)->getIsObj()){
				//continue the recurrsion
				numLinesLeft=displayObj((ObjField*)obj->getField(i),numLinesLeft,numTabs);
			}else{
				//just a field
				printLineNumAndTabs(obj->getField(i)->getLineNumber(),numTabs);
				for(std::string s: obj->getField(i)->getText()){
					printf(" %s",s.c_str());
				}
				printf("\n");
				numLinesLeft--;
			}
		}
	}else{
		//just print the closed Object
		printLineNumAndTabs(obj->getLineNumber(),numTabs);
		printf(" " NEGATIVE_PLUS " %s" "\n",obj->getName().c_str());
		numLinesLeft--;
	}
	return numLinesLeft;
}

void DisplayManager::printLineNumAndTabs(int lineNum,int numTabs){
	printf("% 4d |%.*s",lineNum,numTabs*2,LOTS_OF_SPACE);
}

//function from Microsoft
bool DisplayManager::EnableVTMode()
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
	
	//this part is from stack overflow
	//this disables console echo
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	//printf(ESC"(B");
	
    return true;
}
void DisplayManager::getCurrsorPos(int* row,int* col){
	printf(CSI "6n");
	char bufferRow[10];
	char bufferCol[10];
	int pos=0;
	char in;
	while ((in=getchar())<=0x30 || (in>=0x39));
	do{
		bufferRow[pos]=in;
		pos++;
	}while((in=getchar())!=';');
	bufferRow[pos]='\0';
	pos=0;
	while ((in=getchar())<=0x30 || (in>=0x39));
	do{
		bufferCol[pos]=in;
		pos++;
	}while((in=getchar())!='R');
	bufferCol[pos]='\0';
	//printf("row: %send",bufferRow);
	*row=std::stoi(bufferRow);
	//printf("col: %send",bufferCol);
	*col=std::stoi(bufferCol);
}
void DisplayManager::updateScreenSize(){
	printf("\nResize window now then press enter three times to continue...");
	while(getchar()!='\n'){
		Sleep(10);
	}
	//store the current currsor position
	int currsorRow;
	int currsorCol;
	getCurrsorPos(&currsorRow,&currsorCol);
	//move currsor to bottom right
	printf(CSI "250;250H");
	
	//get cursor position to get sreen size
	getCurrsorPos(&numRows,&numCols);
	
	//restore currsor
	printf(CSI "%d;%dH\n",currsorRow,currsorCol);
}