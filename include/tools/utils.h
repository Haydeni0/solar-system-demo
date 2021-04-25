#ifndef UTILS_H_202104
#define UTILS_H_202104

#include <windows.h>

typedef UINT32 u32;

struct RenderState
{ // Container for the global render state
    void *memory;
    int width;
    int height;
    BITMAPINFO bitmap_info;
};


// Assert that the value is within the x memory bounds
void assertMemoryBoundsx(int x);
// Assert that the value is within the y memory bounds
void assertMemoryBoundsy(int y);
// Clamp a value between min and max (inline for performance)
int clamp(int val, int min, int max);





#endif