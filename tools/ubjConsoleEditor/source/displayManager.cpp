#include "displayManager.h"

//constructor
DisplayManager::DisplayManager(ObjField* fields,std::string fileName,ObjField* formatTemplates){
	this->console=new Console(fileName+" - UBJ Console Editor");
	this->fields=fields;
	this->formatTemplates=formatTemplates;
	
	this->currentMenu=Menu::Main;
	
	//bottom bar stuff
	this->bottomBarIsVisable=true;
	this->bottomBarVisabilityChanged=true;
	this->testText=BottomBarText("r - check for console resize\ne - expand/colapse object/array");
	this->currentBotBar=&testText;
	
	this->currentRowNum=0;
	this->currentColNum=1;
	this->currentLineNum=1;
	this->currentField=(Field*)fields;
	this->currentNumTabs=0;
	
}
	
//getters and setters
void DisplayManager::setCurrentLineNum(int val){ this->currentRowNum=val; } //do not use
int DisplayManager::getCurrentLineNum(){ return this->currentField->getLineNumber(); }
void DisplayManager::setCurrentRowNum(int val){ this->currentRowNum=val; }
int DisplayManager::getCurrentRowNum(){ return this->currentRowNum; }
void DisplayManager::setCurrentColNum(int val){ this->currentColNum=val; }
int DisplayManager::getCurrentColNum(){ return this->currentColNum; }
void DisplayManager::togleUnderlineCursor(){
	this->underlineCursorVisable=!this->underlineCursorVisable;
	this->displayCurrentLine();
}
void DisplayManager::turnOnUnderlineCursor(){
	this->underlineCursorVisable=true;
	this->displayCurrentLine();
}
void DisplayManager::turnOffUnderlineCursor(){
	this->underlineCursorVisable=false;
	this->displayCurrentLine();
}

//alt setters
void DisplayManager::underlineCursorUp(){
	//temparaily turn the cursor off
	this->turnOffUnderlineCursor();
	
	//find the next line up
	Field* previous=this->fields->findPrevious(this->currentField->getLineNumber());
	if(previous==NULL || previous==this->fields){
		//reached top of ducument
		this->turnOnUnderlineCursor();
		return;
	}
	this->currentField=previous;
	this->currentNumTabs=this->fields->findLevel(this->currentField->getLineNumber(),0);
	//see if scrolling need to happen
	if(this->currentRowNum<=1) this->scrolUpMainSection(true);
	else this->currentRowNum--;
	this->turnOnUnderlineCursor();
}
void DisplayManager::underlineCursorDown(){
	//if(this->currentRowNum>=(console->getNumRows()-this->currentBotBar->getBottomBarHeigth()))return;
	//temparaily turn the cursor off
	this->turnOffUnderlineCursor();
	
	//find the next line down
	Field* next=this->fields->findNext(this->currentField->getLineNumber());
	if(next==NULL){
		this->turnOnUnderlineCursor();
		return;
	}
	this->currentField=next;
	this->currentNumTabs=this->fields->findLevel(this->currentField->getLineNumber(),0);
	//see if scrolling need to happen
	if(this->currentRowNum>=console->getNumRows()-this->currentBotBar->getBottomBarHeigth()) this->scrolDownMainSection(true);
	else this->currentRowNum++;
	this->turnOnUnderlineCursor();
}
void DisplayManager::underlineCursorLeft(){
	this->currentColNum=(this->currentColNum==0)?0:this->currentColNum-1;
	this->displayCurrentLine();
}
void DisplayManager::underlineCursorRight(){
	this->currentColNum=(this->currentColNum==2)?2:this->currentColNum+1;
	this->displayCurrentLine();
}
void DisplayManager::enter(){
	if(this->currentField->getIsObj()){
		((ObjField*)this->currentField)->toggelExpantion();
	}
	this->fullDisplayUpdate();
}


//display functions
void DisplayManager::fullDisplayUpdate(){
	//erase screen
	console->clearAll();
	//disregaurding top/bottom bar
	//keep cursor at top for now
	console->setCursor(1,1);
	this->displayObj(this->fields,console->getNumRows()-testText.getBottomBarHeigth(),0,false);
	testText.display(console,true);
}
void DisplayManager::displayLoop(){
	char in;
	InputCmd cmd;
	while(true){
		in=getchar();
		//check how to handle the input based on the mode
		if(in==ESC){
			cmd=console->getCmd();
			switch(cmd){
				case ConsoleSizeChanged:
					this->fullDisplayUpdate();
					break;
				case Up:
					this->underlineCursorUp();
					break;
				case Down:
					this->underlineCursorDown();
					break;
				case Left:
					this->underlineCursorLeft();
					break;
				case Right:
					this->underlineCursorRight();
					break;
				
			}
		}else{
			switch(in){
				case 'e':
				case '\n':
					this->enter();
					break;
				case 'r':
					console->checkForResize();
					break;
			}
		}
		//testText.setText("this->currentRowNum: %d"+std::to_string(this->currentRowNum)+"\nthis->currentLineNum: %d"+std::to_string(this->currentLineNum));
		testText.display(console,false);
		//this->console->setCursorVisable(false);
	}
}
//display helper functions
/*void DisplayManager::displayBottomBar(){
	//if the bar is not visable then don't display it
	if(this->bottomBarIsVisual==false)return;
	if(bottomBarVisabilityChanged){
		//need to print the top bar
		console->setCursor(1,console->getNumRows()-this->bottomBarSize);
		console->clearAllAfterCursor();
		for(int a=1;a<console->getNumCols();a++) print("-");
		console->setCursor(1,console->getNumRows()-this->bottomBarSize+1);
	}else{
		console->setCursor(1,console->getNumRows()-this->bottomBarSize+1);
		console->clearAllAfterCursor();
	}
	//print the topString
	if(this->bottomBarType!=BottomBarType::None)print(this->bottomBarText);
	//decide witch type it is
	switch(this->bottomBarType){
		case TextInput:
			
			break;
		case List:
			
			break;
	}
}*/

int DisplayManager::displayObj(ObjField* obj,int numLinesLeft,int numTabs, bool displayHeader){
	if(numLinesLeft<=0)return 0;
	std::vector<std::string> text;
	//charck if the Obj is expanded or not
	if(obj->getIsExpanded()){
		//all sub fields will need to be printed
		//print the header
		if(displayHeader){
			displayObj(obj,console->getNumRows()-numLinesLeft-this->currentBotBar->getBottomBarHeigth()+1,numTabs);
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
				displayVal((ValField*) obj->getField(i),console->getNumRows()-numLinesLeft-this->currentBotBar->getBottomBarHeigth()+1,numTabs);
				numLinesLeft--;
			}
		}
	}else if(displayHeader){
		//just print the closed Object
		displayObj(obj,console->getNumRows()-numLinesLeft-this->currentBotBar->getBottomBarHeigth()+1,numTabs);
		numLinesLeft--;
	}
	return numLinesLeft;
}
void DisplayManager::displayObj(ObjField* obj,int rowNum,int numTabs){
	printLineNumAndTabs(obj->getLineNumber(),numTabs);
	if(rowNum==this->currentRowNum && this->underlineCursorVisable) printf(BEGIN_UNDERLINE);
	if(obj->getIsExpanded()) printf(" " NEGATIVE_MINUS " %s",obj->getName().c_str());
	else printf(" " NEGATIVE_PLUS " %s",obj->getName().c_str());
	if(rowNum==this->currentRowNum && this->underlineCursorVisable){
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
		if(rowNum==this->currentRowNum && this->currentColNum==a && this->underlineCursorVisable){
			printf(" %s",Console::underlineText(text.at(a)).c_str());
			this->currentField=val;
			this->currentNumTabs=numTabs;
		}
		else printf(" %s",text.at(a).c_str());
	}
	printf("\n");
}
void DisplayManager::printLineNumAndTabs(int lineNum,int numTabs){
	printf("% 4d |",lineNum);
	std::string spaces="";
	for(int a=0;a<numTabs;a++)spaces+="  ";
	printf("%s",spaces.c_str());
}

void DisplayManager::displayCurrentLine(){
	if(this->currentRowNum==0)return;
	if(this->currentField->getLineNumber()==0)return;
	//move cursor to the current line
	console->setCursor(1,this->currentRowNum);
	
	//remove the current line
	console->clearCurrentLine();
	
	console->setCursor(1,this->currentRowNum);
	
	//rewrite the line
	printLineNumAndTabs(this->currentField->getLineNumber(),this->currentNumTabs);
	if(this->currentField->getIsObj()){
		if(this->underlineCursorVisable)printf(BEGIN_UNDERLINE);
		if(((ObjField*) this->currentField)->getIsExpanded()) printf(" " NEGATIVE_MINUS " %s",((ObjField*) this->currentField)->getName().c_str());
		else printf(" " NEGATIVE_PLUS " %s",((ObjField*) this->currentField)->getName().c_str());
		if(this->underlineCursorVisable)printf(END_UNDERLINE);
	}else{
		std::vector<std::string> text=this->currentField->getText();
		for(int a=0;a<text.size();a++){
			if(this->currentColNum==a && this->underlineCursorVisable){
				printf(" %s",Console::underlineText(text.at(a)).c_str());
			}
			else printf(" %s",text.at(a).c_str());
		}
	}
}
void DisplayManager::scrolUpMainSection(bool newCurrent){
	//remove line aboave bottom bar
	console->setCursor(1,console->getNumRows()-this->currentBotBar->getBottomBarHeigth()-1);
	console->deleteLines(1);
	//inset line at top
	console->setCursor(1,1);
	console->insertLineAbove(1);
	//display the new line
	if(newCurrent){
		this->displayCurrentLine();
		return;
	}else{
		//go find the line
		//
		//
		// TODO TODO
		//
		//
	}
}
void DisplayManager::scrolDownMainSection(bool newCurrent){
	//remove top line
	console->setCursor(1,1);
	console->deleteLines(1);
	//inset line aboave bottom bar
	console->setCursor(1,console->getNumRows()-this->currentBotBar->getBottomBarHeigth());
	console->insertLineAbove(1);
	//display the new line
	if(newCurrent){
		this->displayCurrentLine();
		return;
	}else{
		//go find the line
		//
		//
		// TODO TODO
		//
		//
	}
}