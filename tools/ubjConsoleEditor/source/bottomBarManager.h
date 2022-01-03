#ifndef BOTTOM_BAR_MANAGER_H
#define BOTTOM_BAR_MANAGER_H

#include <string.h>

#include "console.h"
#include "bottomBarType.h"
#include "inputCmd.h"

class BottomBarManager{
	private:
		BottomBarType type;
		int bottomBarHeigth;
		Console* console;
	public:
		static const int bottomBarMaxHeigth=8;
	public:
		BottomBarManager(Console* console,BottomBarType type,int bottomBarHeigth);
		
		//returns the current heigth of the bar
		int getBottomBarHeigth();
		
		//takes in keypress and displays the bar
		//returns true if bar function is done
		virtual bool keypress(char c, InputCmd cmd);
		
		//displays the bottom bar
		virtual void display(bool drawEverything);
		
		//utility function
		static int numLinesInString(std::string s);
		
	protected:
		bool setBottomBarHeigth(int heigth);
		
		void displayBlankBottomBar(Console* console);
		
};

#endif