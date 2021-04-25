/*
Program to get a gui in windows
Based on tutorials: https://www.youtube.com/watch?v=yD0WzbKJcOg&ab_channel=DanZaidan
*/

#include "tools/utils.h"
#include "gui/input_handling.h"
#include "gui/renderer.h"
#include "gui/platform_common.h"
#include <tchar.h> // For converting const char * to LPCSTR

// GLOBALS
bool running{true};
RenderState render_state;

LRESULT window_callback(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    /* 
    An application-defined function that processes messages sent to a window. The WNDPROC type defines a pointer to this callback function.
    The "Window procedure".
    */
    LRESULT result{0};
    switch (uMsg)
    {
    case WM_CLOSE: // If a message is sent such that the window should be closed, stop running.
    case WM_DESTROY:
    {
        running = false;
    }
    break;
    case WM_SIZE:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        render_state.width = rect.right - rect.left;
        render_state.height = rect.bottom - rect.top;

        int buffer_size{static_cast<int>(render_state.width * render_state.height * sizeof(unsigned int))};

        if (render_state.memory)
            VirtualFree(render_state.memory, 0, MEM_RELEASE);
        render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
        render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
        render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
        render_state.bitmap_info.bmiHeader.biPlanes = 1;
        render_state.bitmap_info.bmiHeader.biBitCount = 32;
        render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
    }
    break;

    default:
    {
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    }

    return result;
}

void parseVKInputs(const MSG &message, Input &input)
{ // Look for inputs in the message and record them
    switch (message.message)
    {
    case WM_KEYUP: // If a button is pressed/released, do something
    case WM_KEYDOWN:
    {
        u32 vk_code{(u32)message.wParam}; // Type of button
        bool is_down{(message.lParam & (1 << 31)) == 0};
        // Define a macro to simplify addition of buttons to the code (is this evil?)
#define PROCESS_BUTTON(b, vk)               \
    case vk:                                \
    {                                       \
        input.buttons[b].is_down = is_down; \
        input.buttons[b].changed = true;    \
    }                                       \
    break;
        // Change input based on the key pressed
        switch (vk_code)
        {
            PROCESS_BUTTON(BUTTON_UP, VK_UP);
            PROCESS_BUTTON(BUTTON_DOWN, VK_DOWN);
            PROCESS_BUTTON(BUTTON_LEFT, VK_LEFT);
            PROCESS_BUTTON(BUTTON_RIGHT, VK_RIGHT);
            PROCESS_BUTTON(BUTTON_SPACE, VK_SPACE);
            PROCESS_BUTTON(BUTTON_OEM_MINUS, VK_OEM_MINUS);
            PROCESS_BUTTON(BUTTON_OEM_PLUS, VK_OEM_PLUS);
        }
    }
    }
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{ // Program entry point

    // Create window class

    WNDCLASS window_class{};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = _T("Game Window Class");
    window_class.lpfnWndProc = window_callback;

    // Register Class
    RegisterClass(&window_class);

    // Create window
    int default_width{900};
    int default_height{900};
    HWND window = CreateWindow(window_class.lpszClassName, _T("Solar System"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, default_width, default_height, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);

    Input input{};

    float delta_time; // Frame time in seconds
    LARGE_INTEGER frame_begin_time; // Frame begin time in cpu cycles
    QueryPerformanceCounter(&frame_begin_time);

    float performance_frequency; // Clock frequency in cycles per second
    {
        LARGE_INTEGER perf;
        QueryPerformanceFrequency(&perf);
        performance_frequency = static_cast<float>(perf.QuadPart);
    }

    // Running loop
    // Each iteration is one frame
    while (running)
    {
        // Input
        MSG message;

        // Reset the 'changed' field inside input at the start of every frame
        for (int i{0}; i < BUTTON_COUNT; i++)
        {
            input.buttons[i].changed = false;
        }

        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            // Search message for keyboard inputs
            parseVKInputs(message, input);

            TranslateMessage(&message);
            DispatchMessage(&message); // Send message to the windows procedure
        }

        // Simulate
        renderBackground();
        inputHandler(input);

        // Render
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

        // Get frame end time
        LARGE_INTEGER frame_end_time; // Frame end time in cpu cycles
        QueryPerformanceCounter(&frame_end_time);
        // Find the frame time in seconds
        delta_time = static_cast<float>(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
        frame_begin_time = frame_end_time;   
        if (delta_time);
    }

    return 0;
}
