#ifndef GLOBALS_H
#define GLOBALS_H
//global vatiables like settings
namespace Globals{
	
	//deterines if/where the type will be displayed
	//0: not displayed
	//1: display in middle (shortened)
	//2: end display
	//3: end display (shortened)
	extern int displayValueFieldType;
	
	//determines how flaots and doubles are displayed
	//0: full percistion (no rounding/truncating
	//1: use the display lengths
	extern int displayDecimalType;
	extern int displayFloatNumber;
	extern int displayDoubleNumber;
	
}

//error list
#define ERROR_NONE			0
#define ERROR_UNKNOWN		1
#define ERROR_UNEXPED_TYPE	2
#define ERROR_UNEXPED_CHAR	3


#endif