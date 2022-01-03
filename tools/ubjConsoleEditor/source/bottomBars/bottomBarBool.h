#ifndef BOTTOM_BAR_Bool_H
#define BOTTOM_BAR_Bool_H

#include "../bottomBarManager.h"

class BottomBarBool:public BottomBarManager{
	protected:
		std::string question;
		bool answer;
	public:
		BottomBarBool(Console* console);
		BottomBarBool(Console* console,std::string tquestion);
		std::string getQuestion();
		bool getAnswer();
		virtual bool keypress(char c, InputCmd cmd);
		virtual void display(bool drawEverything);
	private:
		void printYN(bool moveCursor);		
};

#endif