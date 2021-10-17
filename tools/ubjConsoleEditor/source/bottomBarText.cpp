#include "bottomBarText.h"

BottomBarText::BottomBarText():BottomBarManager(BottomBarType::Text,2){
	this->text="";
	this->textChanged=true;
}
BottomBarText::BottomBarText(std::string text):BottomBarManager(BottomBarType::Text,1+BottomBarManager::numLinesInString(text)){
	this->text=text;
	this->textChanged=true;
}
std::string BottomBarText::getText(){ return this->text; }
void BottomBarText::setText(std::string text){
	this->text=text;
	this->textChanged=true;
	setBottomBarHeigth(1+BottomBarManager::numLinesInString(text));
}
void BottomBarText::display(Console* console,bool drawEverything){
	if(drawEverything || this->textChanged){
		displayBlankBottomBar(console);
		printf("%s",this->text.c_str());
	}
	this->textChanged=false;
}