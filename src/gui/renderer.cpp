
#include "gui/renderer.h"
#include "tools/utils.h"

// Forward declarations of global variables
extern bool running;
extern RenderState render_state;

void renderBackground()
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

void clearScreen(u32 colour)
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

void drawRectPixels(int x0, int y0, int x1, int y1, u32 colour)
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

void drawRect(float x, float y, float width, float height, u32 colour)
{
    // Takes inputs in proportion of screen width/height, between 0 and 100.
    float render_scale{0.01};

    // Scale input to the screen size
    x *= render_state.width * render_scale;
    y *= render_state.height* render_scale;
    width *= render_state.width* render_scale;
    height *= render_state.height* render_scale;

    // Convert to pixels
    int x0{static_cast<int>(x - width / 2)};
    int x1{static_cast<int>(x + width / 2)};
    int y0{static_cast<int>(y - height / 2)};
    int y1{static_cast<int>(y + height / 2)};
    drawRectPixels(x0, y0, x1, y1, colour);
}
