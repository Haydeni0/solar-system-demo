#ifndef RENDERER_H_202104
#define RENDERER_H_202104

#include "tools/utils.h"

// Render the background screen
void renderBackground();
// Render a colour covering the entire screen
void clearScreen(u32 colour);
// Draw a rectangle with bottom left and top right pixel coordinates (x0, y0) and (x1, y1)
void drawRectPixels(int x0, int y0, int x1, int y1, u32 colour);
// Draw a rectangle at screen location (in screen widths) (x, y) with specified width and height
void drawRect(float x, float y, float width, float height, u32 colour);

#endif