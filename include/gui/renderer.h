#ifndef RENDERER_H_202104
#define RENDERER_H_202104

#include "tools/utils.h"

// Render the background screen
void render_background();
// Render a colour covering the entire screen
void clear_screen(u32 colour);
// Draw a rectangle with bottom left and top right pixel coordinates (x0, y0) and (x1, y1)
void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 colour);
// Draw a rectangle at screen location (in screen widths) (x, y) with specified width and height
void draw_rect(float x, float y, float width, float height, u32 colour);

#endif