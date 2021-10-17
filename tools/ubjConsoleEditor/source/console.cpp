#include "console.h"
const std::string Console::applyBold=CSI "1m";
const std::string Console::removeBold=CSI "22m";
const std::string Console::applyUnderline=CSI "4m";
const std::string Console::removeUnderline=CSI "24m";
const std::string Console::applyNegative=CSI "7m";
const std::string Console::removeNegative=CSI "27m";

Console::Console(std::string name){
	printf("Setting up console ...\n");
	if(!windowsConsoleSetup()){
		printf("Console setup failed durring OS calls\nErrorCode: %d\n",GetLastError());
	}
	//set window name
	this->setName(name);
	//make shure they are returned to the default position
	this->cursorX=1;
	this->cursorY=1;
	//start with a screan size of 0;
	this->numRows=0;
	this->numCols=0;
	this->checkForResize();
	//go through the input stream to get the console size
	char c;
	InputCmd cmd;
	do{
		c=getchar();
		//printf("Recived0: %02hhx                 \n",c);
		if(c==ESC){
			cmd=this->getCmd();
			if(cmd==InputCmd::ConsoleSizeChanged) break;
			else if(cmd==InputCmd::ConsoleSizeNoChange){
				printf("Intial console size not found");
			}
		}
	}while(true);
	printf("resizing is done\n");
	//make cursor invisable at begining
	this->setCursorBlinking(false);
	this->setCursorVisable(false);
	printf("Console setup compleat\n");
	this->clearAll();
}

//getters
int Console::getNumRows(){ return this->numRows; }
int Console::getNumCols(){ return this->numCols; }
int Console::getCursorX(){ return this->cursorX; }
int Console::getCursorY(){ return this->cursorY; }
bool Console::isCursorVisable(){ return this->cursorVisable; }
bool Console::isCursorBlinking(){ return this->cursorBlinking; }
std::string Console::getName(){ return this->name; }

//seters/updators
void Console::checkForResize(){
	this->setCursor(10000,10000);
	printf(CSI "6n");
	this->setCursor(0,0);
}
void Console::setCursor(int x,int y){ printf(CSI "%d;%dH",y,x); }
void Console::setCursorX(int x){ printf(CSI "%d;%dG",x); }
void Console::setCursorY(int y){ printf(CSI "%d;%dd",y); }
void Console::cursorUp(int moveBy){ printf(CSI "%dA",moveBy); }
void Console::cursorDown(int moveBy){ printf(CSI "%dB",moveBy); }
void Console::cursorLeft(int moveBy){ printf(CSI "%dD",moveBy); }
void Console::cursorRight(int moveBy){ printf(CSI "%dC",moveBy); }
void Console::setCursorVisable(bool val){
	this->cursorVisable=val;
	if(val)printf(CSI "?25h");
	else printf(CSI "?25l");
}
void Console::setCursorBlinking(bool val){
	this->cursorBlinking=val;
	if(val)printf(CSI "?12h");
	else printf(CSI "?12l");
}
void Console::setName(std::string name){
	this->name=name;
	printf(OSI "2;%s\x07",name.c_str());
}

//clearing commands
void Console::clearAll(){ printf(CSI "2J"); }
void Console::clearCurrentLine(){ printf(CSI "2K"); }
void Console::clearAllAfterCursor(){ printf(CSI "0J"); } //Note: includes cursor position
void Console::clearCurrentLineAfterCursor(){ printf(CSI "0K"); } //Note: includes cursor position
void Console::clearAllBeforeCursor(){ printf(CSI "1K"); }
void Console::clearCurrentLineBeforeCursor(){ printf(CSI "1J"); }

void Console::clearCurrentChar(){ this->clearCurrentChar(); }
void Console::clearChars(int num){ printf(CSI "%dX",num); }

//insert/remove
void Console::insertSpaces(int num){ printf(CSI "%d@",num); }
void Console::deleteChars(int num){ printf(CSI "%dP",num); }
void Console::insertLineAbove(int num){ printf(CSI "%dL",num); }
void Console::deleteLines(int num){ printf(CSI "%dM",num); }

//get input commands
InputCmd Console::getCmd(){
	//Asumes ECS has already been recived
	//[ or O expected as next char
	int in=getchar();
	char first;
	if(in==EOF) return InputCmd::Esc;
	//printf("Recived1: %02hhx                 \n",in);
	first=in;
	//now a list of arguments
	char argc=0;
	char argcMax=10;
	int argv[10];
	int c;
	std::string num="";
	bool moreToParse=false;
	do{
		moreToParse=false;
		c=getchar();
		//printf("Recived2: %02hhx                 \n",c);
		if(c<='9' && c>='0'){
			num+=c;
			moreToParse=true;
		}if(c==';'){
			//parse the current std::string as a number
			argv[argc]=std::stoi(num);
			//printf("Number Recived: %d                 \n",argv[argc]);
			argc++;
			num="";
			moreToParse=true;
		}
		//printf("num: %s                 \n",num.c_str());
	}while(moreToParse);
	if(num!=""){
		argv[argc]=std::stoi(num);
		//printf("Number Recived: %d                 \n",argv[argc]);
		argc++;
	}
	//printf("first: 0x%02hhx                 \n",first);
	//printf("c: %c                 \n",c);
	//printf("argc: %d                 \n",argc);
	char last;
	if(first=='['){
		last=c;
		switch(last){
			case 'A':
				if(argc==2 && argv[0]==1 && argv[1]==5)return InputCmd::CtrlUp;
				else if(argc==0) return InputCmd::Up;
			case 'B':
				if(argc==2 && argv[0]==1 && argv[1]==5)return InputCmd::CtrlDown;
				else if(argc==0) return InputCmd::Down;
			case 'C':
				if(argc==2 && argv[0]==1 && argv[1]==5)return InputCmd::CtrlRight;
				else if(argc==0) return InputCmd::Right;
			case 'D':
				if(argc==2 && argv[0]==1 && argv[1]==5)return InputCmd::CtrlLeft;
				else if(argc==0) return Left;
			case '~':
				if(argc==1)switch(argv[0]){
					case 2:
						return InputCmd::Insert;
					case 3:
						return InputCmd::Delete;
					case 5:
						return InputCmd::PageUp;
					case 6:
						return InputCmd::PageDown;
					case 15:
						return InputCmd::F5;
					case 17:
						return InputCmd::F6;
					case 18:
						return InputCmd::F7;
					case 19:
						return InputCmd::F8;
					case 20:
						return InputCmd::F9;
					case 21:
						return InputCmd::F10;
					case 23:
						return InputCmd::F11;
					case 24:
						return InputCmd::F12;
					
				}
			case 'R':
				if(argc==2){
					bool changed=(numRows!=argv[0]) || (numCols!=argv[1]);
					numRows=argv[0];
					numCols=argv[1];
					if(changed)return InputCmd::ConsoleSizeChanged;
					else return InputCmd::ConsoleSizeNoChange;
				}
			
		}
	}else if(first=='O'){
		last=c;
		switch(last){
			case 'A':
				return InputCmd::Up;
			case 'B':
				return InputCmd::Down;
			case 'C':
				return InputCmd::Right;
			case 'D':
				return InputCmd::Left;
			case 'P':
				return InputCmd::F1;
			case 'Q':
				return InputCmd::F2;
			case 'R':
				return InputCmd::F3;
			case 'S':
				return InputCmd::F4;			
		}
	}else if(c==EOF){
		return InputCmd::AltCode;
	}
	return InputCmd::NoCmd;
}
unsigned char Console::getCtrlChar(unsigned char c){ return c+0x40; }
//std::string Console::getString(int maxRawLength, bool parseSlashes); //assumes cursor has already been positioned

//OS specific items
//function partialy from Microsoft
//works for Microsoft
bool Console::windowsConsoleSetup(){
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0 | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
	printf("Output: %08hhx",dwMode);
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
	
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE)
    {
        return false;
    }

	dwMode=ENABLE_VIRTUAL_TERMINAL_INPUT;
	printf("Input: %08hhx",dwMode);
	if (!SetConsoleMode(hIn, dwMode))
    {
        return false;
    }
    return true;
}
//static format comands
std::string Console::boldText(std::string str){ return Console::applyBold+str+Console::removeBold; };
std::string Console::underlineText(std::string str){ return Console::applyUnderline+str+Console::removeUnderline; };
std::string Console::negateText(std::string str){ return Console::applyNegative+str+Console::removeNegative; };