#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <cstdio>
#include <vector>
#include <string>
#include <windows.h>
#include <wchar.h>
#include <iostream>

#include "bottomBarType.h"
#include "field.h"
#include "objField.h"

//basic sequences
#define ESC "\x1b"
#define CSI "\x1b["
#define OSI "\x1b]"
#define BELL "\x07"

//common commands
#define BEGIN_UNDERLINE "\x1b[4m"
#define END_UNDERLINE "\x1b[24m"
#define NEGATIVE "\x1b[7m"
#define POSITIVE "\x1b[27m"
#define NEGATIVE_PLUS "\x1b[7m+\x1b[27m"
#define NEGATIVE_MINUS "\x1b[7m-\x1b[27m"

#define LOTS_OF_TABS "\t\t\t\t\t\t\t\t\t\t\t\t"
#define LOTS_OF_SPACE "                                                "

class DisplayManager{
	private:
		ObjField* fields;
		
		//document based line number
		int currentLineNum;
		int maxLineNum;
		
		//the current currsor position
		int currentRowNum;
		int currentColNum;
		
		//console dimentions
		int numCols;
		int numRows;
		
		//current bottom bar type
		BottomBarType bottomBar;
	
	//constructor
	public:
		DisplayManager(ObjField*,std::string);
	
	//getters and setters
	public:
		void setCurrentLineNum(int);
		int getCurrentLineNum();
		void setCurrentRowNum(int);
		int getCurrentRowNum();
		void setCurrentColNum(int);
		int getCurrentColNum();
	
	//alt setters
	public:
		void cursorUp();
		void cursorDown();
		void cursorLeft();
		void cursorRight();
	
	
	//display functions
	public:
		void updateDisplay();
	//helper functions
	private:
		int displayObj(ObjField* obj,int numLinesLeft,int numTabs);
		void printLineNumAndTabs(int lineNum,int numTabs);
		bool EnableVTMode();
		void getCurrsorPos(int*,int*);
		void updateScreenSize();
	
};


#endif