#ifndef INPUT_HANDLING_H_202104
#define INPUT_HANDLING_H_202104

#include "gui/platform_common.h"

bool held(Input &input, Button_Type BUTTONTYPE);
bool pressed(Input &input, Button_Type BUTTONTYPE);
bool released(Input &input, Button_Type BUTTONTYPE);

void inputHandler(Input &input);


#endif
