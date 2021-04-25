

#include "gui/input_handling.h"
#include "gui/renderer.h"

bool held(Input &input, Button_Type BUTTONTYPE)
{
    return input.buttons[BUTTONTYPE].is_down;
}
bool pressed(Input &input, Button_Type BUTTONTYPE)
{
    return (input.buttons[BUTTONTYPE].is_down && input.buttons[BUTTONTYPE].changed);
}
bool released(Input &input, Button_Type BUTTONTYPE)
{
    return (!input.buttons[BUTTONTYPE].is_down && input.buttons[BUTTONTYPE].changed);
}

void inputHandler(Input &input)
{
    if (held(input, BUTTON_UP))
            drawRect(40, 50, 28, 13, 0xff0000);
}
