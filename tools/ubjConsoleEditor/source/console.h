#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include "windows.h"

#include "inputCmd.h"

//basic sequences
#define ESC 27//'\x1b'
#define CSI "\x1b["
#define OSI "\x1b]"
#define BELL 7//'\x07'

#define NEGATIVE_PLUS "\x1b[7m+\x1b[27m"
#define NEGATIVE_MINUS "\x1b[7m-\x1b[27m"

class Console{
	private:
		std::string name;
		int numRows; //Y dimention
		int numCols; //X dimention
		
		//will get invalidated anythime printf() is used
		//they will be updated if getCMD recives a cursor report
		int cursorX;
		int cursorY;
		
		bool cursorVisable;
		bool cursorBlinking;
	
	public:
		static const std::string applyBold;
		static const std::string removeBold;
		static const std::string applyUnderline;
		static const std::string removeUnderline;
		static const std::string applyNegative;
		static const std::string removeNegative;
		
	public:
		Console(std::string name);
		
		//getters
		int getNumRows();
		int getNumCols();
		int getCursorX();
		int getCursorY();
		bool isCursorVisable();
		bool isCursorBlinking();
		std::string getName();
		
		//seters/updators
		void checkForResize(); //sets cursor to 0, 0
		void setCursor(int x,int y);
		void setCursorX(int x);
		void setCursorY(int y);
		void cursorUp(int moveby);
		void cursorDown(int moveby);
		void cursorLeft(int moveby);
		void cursorRight(int moveby);
		void setCursorVisable(bool);
		void setCursorBlinking(bool);
		void setName(std::string name);
		
		//clearing commands
		void clearAll();
		void clearCurrentLine();
		void clearAllAfterCursor(); //Note: includes cursor position
		void clearCurrentLineAfterCursor(); //Note: includes cursor position
		void clearAllBeforeCursor();
		void clearCurrentLineBeforeCursor();
		void clearChar(int x,int y);
		void clearCurrentChar();
		void clearChars(int num);
		
		//insert/remove
		void insertSpaces(int num);
		void deleteChars(int num);
		void insertLineAbove(int num);
		void deleteLines(int num);
		
		//get input commands
		InputCmd getCmd(); //Asumes ECS has already been recived
		unsigned char getCtrlChar(unsigned char c);
		//std::string getString(int maxRawLength, bool parseSlashes); //assumes cursor has already been positioned
		
	private:
		//OS specific items
		bool windowsConsoleSetup();
	
	public:
		//static format comands
		static std::string boldText(std::string str);
		static std::string underlineText(std::string str);
		static std::string negateText(std::string str);
};

#endif