#ifndef BOTTOM_BAR_MANAGER_H
#define BOTTOM_BAR_MANAGER_H

#include <string.h>

#include "console.h"
#include "bottomBarType.h"

class BottomBarManager{
	private:
		BottomBarType type;
		int bottomBarHeigth;
	public:
		static const int bottomBarMaxHeigth=8;
	public:
		BottomBarManager(BottomBarType type,int bottomBarHeigth);
		
		int getBottomBarHeigth();
		
		virtual void display(Console* console,bool drawEverything);
		static int numLinesInString(std::string s);
		
	protected:
		bool setBottomBarHeigth(int heigth);
		
		void displayBlankBottomBar(Console* console);
		
};

#endif