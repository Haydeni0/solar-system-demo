#include "tools/utils.h"
#include <iostream>

// Forward declarations of global variables
extern bool running;
extern RenderState render_state;

int clamp(int val, int min, int max)
{
    if (val < min)
        return min;
    else if (val > max)
        return max;
    else
        return val;
}