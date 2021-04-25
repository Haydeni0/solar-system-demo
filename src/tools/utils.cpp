#include "tools/utils.h"
#include <iostream>

// Forward declarations of global variables
extern bool running;
extern RenderState render_state;

void assertMemoryBoundsx(int x)
{
    if (x < 0 || x > render_state.width)
    {
        std::cout << "x (" << x << ") is outside of bounds [0, " << render_state.width << "]\n";
        throw;
    }
}
void assertMemoryBoundsy(int y)
{
    if (y < 0 || y > render_state.height)
    {
        std::cout << "y (" << y << ") is outside of bounds [0, " << render_state.height << "]\n";
        throw;
    }
}

int clamp(int val, int min, int max)
{
    if (val < min)
        return min;
    else if (val > max)
        return max;
    else
        return val;
}