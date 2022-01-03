#include "bottomBarBool.h"

BottomBarBool::BottomBarBool(Console* console):BottomBarManager(console,BottomBarType::Bool,2){
	this->question="";
	this->answer=false;
}
BottomBarBool::BottomBarBool(Console* console,std::string question):BottomBarManager(console,BottomBarType::Bool,2+BottomBarManager::numLinesInString(question)){
	this->question=question;
	this->answer=false;
}
std::string BottomBarBool::getQuestion(){ return this->question; }
bool BottomBarBool::getAnswer(){ return this->answer; }
virtual bool BottomBarManager::keypress(char c, InputCmd cmd){
	if(c==ESC){
		switch (cmd){
			case Left:
				this->answer=false;
				this->printYN(true);
				break;
			case Right:
				this->answer=true;
				this->printYN(true);
				break;
		}
	}else{
		switch (c){
			case 'N':
			case 'n':
				this->answer=false;
				this->printYN(true);
				return true;
				break;
			case 'Y':
			case 'y':
				this->answer=true;
				this->printYN(true);
				return true;
				break;
			case '\n':
				return true;
				break;
		}
	}
	return false;
}
void BottomBarBool::display(bool drawEverything){
	if(drawEverything){
		displayBlankBottomBar(console);
		printf("%s",this->question.c_str());
	}
}
void BottomBarBool::printYN(bool moveCursor){
	if(moveCursor) Console::setCurrsor(1,console->numCols);
	if(this->answer) printf("NO\t"+Console::applyUnderline+"YES"+Console::removeUnderline);
	else printf(Console::applyUnderline+"NO\t"+Console::removeUnderline+"YES");
}