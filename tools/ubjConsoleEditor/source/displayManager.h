#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <cstdio>
#include <vector>
#include <string>
#include <windows.h>
#include <wchar.h>
#include <iostream>

#include "console.h"
#include "bottomBarType.h"
#include "bottomBarManager.h"
#include "bottomBarText.h"
#include "field.h"
#include "objField.h"
#include "menu.h"
#include "inputCmd.h"

//common commands
#define BEGIN_UNDERLINE "\x1b[4m"
#define END_UNDERLINE "\x1b[24m"
#define NEGATIVE "\x1b[7m"
#define POSITIVE "\x1b[27m"

#define LOTS_OF_TABS "\t\t\t\t\t\t\t\t\t\t\t\t"
#define LOTS_OF_SPACE "                                                "

class DisplayManager{
	private:
		Console* console;
		ObjField* fields;
		ObjField* formatTemplates;
		
		//document based line number
		int maxLineNum;
		
		//the current underline cursor position
		int currentRowNum; //starts at 1
		int currentColNum;
		int currentLineNum;
		
		//the current field
		Field* currentField;
		int currentNumTabs;
		
		//current status of underline cursor
		bool underlineCursorVisable;
		
		//for storing which menue the user is acessing
		Menu currentMenu;
		//string inputTextBuffer;
		
		//current bottom bar type
		BottomBarManager* currentBotBar;
		BottomBarText testText;
		bool bottomBarIsVisable;
		bool bottomBarVisabilityChanged;
		
	
	//constructor
	public:
		DisplayManager(ObjField*,std::string,ObjField* formatTemplates);
	
	//getters and setters
	public:
		void setCurrentLineNum(int);
		int getCurrentLineNum();
		void setCurrentRowNum(int);
		int getCurrentRowNum();
		void setCurrentColNum(int);
		int getCurrentColNum();
		
		void togleUnderlineCursor();
		void turnOnUnderlineCursor();
		void turnOffUnderlineCursor();
	
	//alt setters
	public:
		void underlineCursorUp();
		void underlineCursorDown();
		void underlineCursorLeft();
		void underlineCursorRight();
		void enter();
	
	
	//display functions
	public:
		void fullDisplayUpdate();
		void displayLoop();
	//helper functions
	private:
		Field* getPreviosLine(ObjField* obj,int lineNum);
		Field* getNextLine(ObjField* obj,int lineNum);
		
		int displayObj(ObjField* obj,int numLinesLeft,int numTabs, bool displayHeader);
		void displayObj(ObjField* obj,int rowNum,int numTabs);
		void displayVal(ValField* val,int rowNum,int numTabs);
		void displayCurrentLine();
		void printLineNumAndTabs(int lineNum,int numTabs);
		
		void scrolUpMainSection(bool newCurrent);
		void scrolDownMainSection(bool newCurrent);
	
};


#endif