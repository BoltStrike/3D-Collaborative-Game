#include "displayManager.h"

//constructor
DisplayManager::DisplayManager(ObjField* fields,std::string fileName){
	if(!EnableVTMode()){
		printf("Boot Failed");
	}
	//set window name
	printf(OSI "2; %s - UBJ Console Editor\x07",fileName.c_str());
	
	//printf("This is an " CSI "4mUnderline" CSI "24m No Underline\n");
	this->fields=fields;
	updateScreenSize();
	printf("\nnumRows: %d\nnumCols: %d\n",numRows,numCols);
	this->currentRowNum=1;
	this->currentColNum=0;
	this->cursorVisable=true;
	//hide the standard console cursor
	printf( CSI "?25l");
}
	
//getters and setters
void DisplayManager::setCurrentLineNum(int val){ this->currentRowNum=val; } //do not use
int DisplayManager::getCurrentLineNum(){ return this->currentField->getLineNumber(); }
void DisplayManager::setCurrentRowNum(int val){ this->currentRowNum=val; }
int DisplayManager::getCurrentRowNum(){ return this->currentRowNum; }
void DisplayManager::setCurrentColNum(int val){ this->currentColNum=val; }
int DisplayManager::getCurrentColNum(){ return this->currentColNum; }
void DisplayManager::togleCurrsor(){
	this->cursorVisable=!this->cursorVisable;
	this->displayCurrentLine();
}
void DisplayManager::turnOnCurrsor(){
	this->cursorVisable=true;
	this->displayCurrentLine();
}
void DisplayManager::turnOffCurrsor(){
	this->cursorVisable=true;
	this->displayCurrentLine();
}

//alt setters
void DisplayManager::cursorUp(){
	if(this->currentRowNum==1)return;
	//temparaily turn the cursor off
	this->turnOffCurrsor();
	
	//find the next line up
	Field* previous=this->fields->findPrevious(this->currentField->getLineNumber());
	if(previous==NULL)return;
	this->currentField=previous;
	this->currentRowNum--;
	this->turnOnCurrsor();
}
void DisplayManager::cursorDown(){
	if(this->currentRowNum==this->numRows)return;
	//temparaily turn the cursor off
	this->turnOffCurrsor();
	
	//find the next line up
	Field* next=this->fields->findNext(this->currentField->getLineNumber());
	if(next==NULL)return;
	this->currentField=next;
	this->currentRowNum++;
	this->turnOnCurrsor();
}
void DisplayManager::cursorLeft(){
	this->currentColNum=(this->currentColNum==0)?0:this->currentColNum--;
	this->displayCurrentLine();
}
void DisplayManager::cursorRight(){
	this->currentColNum=(this->currentColNum==2)?2:this->currentColNum++;
	this->displayCurrentLine();
}
void DisplayManager::enter(){
	if(this->currentField->getIsObj()){
		((ObjField*)this->currentField)->toggelExpantion();
	}
}


//display functions
void DisplayManager::fullDisplayUpdate(){
	//erase screen
	printf(CSI "2J");
	//disregaurding top/bottom bar
	//heep cursor at top for now
	printf(CSI "0;0H");
	this->displayObj(this->fields,this->numRows,0,false);	
}
void DisplayManager::displayLoop(){
	return;
}

int DisplayManager::displayObj(ObjField* obj,int numLinesLeft,int numTabs, bool displayHeader){
	if(numLinesLeft<=0)return 0;
	std::vector<std::string> text;
	//charck if the Obj is expanded or not
	if(obj->getIsExpanded()){
		//all sub fields will need to be printed
		//print the header
		if(displayHeader){
			displayObj(obj,this->numRows-numLinesLeft,numTabs);
			numLinesLeft--;
		}
		numTabs++;
		//now go through the fields
		for(int i=0;i<obj->getNumFields() && numLinesLeft>0;i++){
			if(obj->getField(i)->getIsObj()){
				//continue the recurrsion
				numLinesLeft=displayObj((ObjField*)obj->getField(i),numLinesLeft,numTabs,true);
			}else{
				//just a field
				displayVal((ValField*) obj->getField(i),this->numRows-numLinesLeft,numTabs);
				numLinesLeft--;
			}
		}
	}else if(displayHeader){
		//just print the closed Object
		displayObj(obj,this->numRows-numLinesLeft,numTabs);
		numLinesLeft--;
	}
	return numLinesLeft;
}
void DisplayManager::displayObj(ObjField* obj,int rowNum,int numTabs){
	printLineNumAndTabs(obj->getLineNumber(),numTabs);
	if(rowNum==this->currentRowNum && this->cursorVisable) printf(BEGIN_UNDERLINE);
	if(obj->getIsExpanded()) printf(" " NEGATIVE_MINUS " %s",obj->getName().c_str());
	else printf(" " NEGATIVE_PLUS " %s",obj->getName().c_str());
	if(rowNum==this->currentRowNum && this->cursorVisable){
		printf(END_UNDERLINE);
		this->currentField=(Field*) obj;
		this->currentNumTabs=numTabs;
	}
	printf("\n");
}
void DisplayManager::displayVal(ValField* val,int rowNum,int numTabs){
	printLineNumAndTabs(val->getLineNumber(),numTabs);
	std::vector<std::string> text=val->getText();
	for(int a=0;a<text.size();a++){
		if(rowNum==this->currentRowNum && this->currentColNum==a && this->cursorVisable){
			printf(" " BEGIN_UNDERLINE "%s" END_UNDERLINE,text.at(a).c_str());
			this->currentField=val;
			this->currentNumTabs=numTabs;
		}
		else printf(" %s",text.at(a).c_str());
	}
	printf("\n");
}
void DisplayManager::printLineNumAndTabs(int lineNum,int numTabs){
	printf("% 4d |%.*s",lineNum,numTabs*2,LOTS_OF_SPACE);
}

void DisplayManager::displayCurrentLine(){
	//move cursor to the current line
	printf(CSI "%d;0H",this->currentRowNum+1);
	
	//remove the current line
	printf(CSI "0K");
	
	//rewrite the line
	printLineNumAndTabs(this->currentField->getLineNumber(),this->currentNumTabs);
	if(this->currentField->getIsObj()){
		if(this->cursorVisable)printf(BEGIN_UNDERLINE);
		if(((ObjField*) this->currentField)->getIsExpanded()) printf(" " NEGATIVE_MINUS " %s",((ObjField*) this->currentField)->getName().c_str());
		else printf(" " NEGATIVE_PLUS " %s",((ObjField*) this->currentField)->getName().c_str());
		if(this->cursorVisable)printf(END_UNDERLINE);
	}else{
		std::vector<std::string> text=this->currentField->getText();
		for(int a=0;a<text.size();a++){
			if(this->currentColNum==a && this->cursorVisable){
				printf(" " BEGIN_UNDERLINE "%s" END_UNDERLINE,text.at(a).c_str());
			}
			else printf(" %s",text.at(a).c_str());
		}
		printf("\n");
	}
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
	//store the current cursor position
	int cursorRow;
	int cursorCol;
	getCurrsorPos(&cursorRow,&cursorCol);
	//move cursor to bottom right
	printf(CSI "250;250H");
	
	//get cursor position to get sreen size
	getCurrsorPos(&numRows,&numCols);
	numRows--;//account for the final \n
	//restore cursor
	printf(CSI "%d;%dH\n",cursorRow,cursorCol);
}