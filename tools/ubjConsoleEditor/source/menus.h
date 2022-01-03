#ifndef MENUS_H
#define MeNUS_H

#include <string.h>
#include "bottomBars.h"
#include "valFeild.h"

//prompts the user to edit the string at the pointer
//returns true if value was changed
bool editFeild(*BottomBar,*std::string);
//promps the user to edit the value in the valFeild
//returns true if value changed
bool editValue(*BottomBar,*valFeild);
std::string editFeild(*BottomBar,std::string);

#endif