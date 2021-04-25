
#include "gui/simulate.h"
#include "gui/renderer.h"

void inputHandler(Input &input)
{
    if (input.buttons[BUTTON_UP].is_down)
            drawRect(40, 50, 28, 13, 0xff0000);
}



