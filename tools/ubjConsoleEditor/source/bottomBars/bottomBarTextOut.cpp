#include "bottomBarTextOut.h"

BottomBarTextOut::BottomBarTextOut(Console* console):BottomBarManager(console,BottomBarType::Text,2){
	this->text="";
	this->textChanged=true;
}
BottomBarTextOut::BottomBarTextOut(Console* console,std::string text):BottomBarManager(console,BottomBarType::Text,1+BottomBarManager::numLinesInString(text)){
	this->text=text;
	this->textChanged=true;
}
std::string BottomBarTextOut::getText(){ return this->text; }
void BottomBarTextOut::setText(std::string text){
	this->text=text;
	this->textChanged=true;
	setBottomBarHeigth(1+BottomBarManager::numLinesInString(text));
}
virtual bool BottomBarManager::keypress(char c, InputCmd cmd){
	return false;
}
void BottomBarTextOut::display(bool drawEverything){
	if(drawEverything || this->textChanged){
		displayBlankBottomBar(console);
		printf("%s",this->text.c_str());
	}
	this->textChanged=false;
}