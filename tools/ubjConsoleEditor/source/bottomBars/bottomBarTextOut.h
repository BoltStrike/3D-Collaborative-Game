#ifndef BOTTOM_BAR_TEXT_OUT_H
#define BOTTOM_BAR_TEXT_OUT_H

#include "../bottomBarManager.h"

class BottomBarTextOut:public BottomBarManager{
	protected:
		std::string text;
		bool textChanged;
	public:
		BottomBarTextOut(Console* console);
		BottomBarTextOut(Console* console,std::string text);
		std::string getText();
		void setText(std::string text);
		virtual bool keypress(char c, InputCmd cmd);
		virtual void display(bool drawEverything);
};

#endif