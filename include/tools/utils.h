#ifndef UTILS_H_202104
#define UTILS_H_202104

#include <windows.h>

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

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