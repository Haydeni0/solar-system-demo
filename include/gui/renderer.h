#ifndef RENDERER_H_202104
#define RENDERER_H_202104

#include "tools/utils.h"

// Render the background screen
void render_background();
// Render a colour covering the entire screen
void clear_screen(u32 colour);
// Draw a rectangle with bottom left coordinates (x0, y0) and top right coordinates (x1, y1)
void draw_rect(int x0, int y0, int x1, int y1, u32 colour);


#endif