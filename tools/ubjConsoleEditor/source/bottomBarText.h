#ifndef BOTTOM_BAR_TEXT_H
#define BOTTOM_BAR_TEXT_H

#include "bottomBarManager.h"

class BottomBarText:public BottomBarManager{
	protected:
		std::string text;
		bool textChanged;
	public:
		BottomBarText();
		BottomBarText(std::string text);
		std::string getText();
		void setText(std::string text);
		virtual void display(Console* console,bool drawEverything);
		
};

#endif