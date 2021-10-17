#include "bottomBarManager.h"

BottomBarManager::BottomBarManager(BottomBarType type,int bottomBarHeigth){
	this->type=type;
	this->bottomBarHeigth=bottomBarHeigth;
}

int BottomBarManager::getBottomBarHeigth(){ return this->bottomBarHeigth; }

bool BottomBarManager::setBottomBarHeigth(int heigth){
	if(heigth<=bottomBarMaxHeigth){
		this->bottomBarHeigth=heigth;
		return true;
	}
	return false;
}

void BottomBarManager::display(Console* console,bool drawEverything){
	if(drawEverything)this->displayBlankBottomBar(console);
}

void BottomBarManager::displayBlankBottomBar(Console* console){
	//position the currsor
	console->setCursor(1,console->getNumRows()-this->getBottomBarHeigth()+1);
	//clear all
	console->clearAllAfterCursor();
	//draw the line
	std::string s;
	for(int a=1;a<=console->getNumCols();a++) s+="-";
	printf("%s\n",s.c_str());
	//set cursor to first usable line
	console->setCursor(1,console->getNumRows()-this->getBottomBarHeigth()+2);
}

int BottomBarManager::numLinesInString(std::string s){
	int num=0;
	for(char c:s){
		if(c=='\n') num++;
	}
	return num+1;
}