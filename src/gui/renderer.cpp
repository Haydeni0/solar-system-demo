
#include "gui/renderer.h"
#include "tools/utils.h"

// Forward declarations of global variables
extern bool running;
extern RenderState render_state;

void render_background()
{
    u32 *pixel = (u32 *)render_state.memory;
    for (int y{0}; y < render_state.height; y++)
    {
        for (int x{0}; x < render_state.width; x++)
        {
            *pixel++ = x * y;
        }
    }
}

void clear_screen(u32 colour)
{
    u32 *pixel = (u32 *)render_state.memory;
    for (int y{0}; y < render_state.height; y++)
    {
        for (int x{0}; x < render_state.width; x++)
        {
            *pixel++ = colour;
        }
    }
}

void draw_rect(int x0, int y0, int x1, int y1, u32 colour)
{

    x0 = clamp(x0, 0, render_state.width);
    x1 = clamp(x1, 0, render_state.width);
    y0 = clamp(y0, 0, render_state.height);
    y1 = clamp(y1, 0, render_state.height);

    for (int y{y0}; y < y1; y++)
    {
        u32 *pixel = (u32 *)render_state.memory + x0 + y * render_state.width;
        for (int x{x0}; x < x1; x++)
        {
            *pixel++ = colour;
        }
    }
}
