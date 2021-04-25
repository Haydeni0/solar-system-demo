/*
Program to get a gui in windows
Based on tutorials: https://www.youtube.com/watch?v=yD0WzbKJcOg&ab_channel=DanZaidan

Note that som
*/

#include "tools/utils.h"
#include "gui/renderer.h"

// GLOBALS
bool running{true};
RenderState render_state;

LRESULT
window_callback(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    /* An application-defined function that processes messages sent to a window. The WNDPROC type defines a pointer to this callback function.*/
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

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{ // Program entry point

    // Create window class

    WNDCLASS window_class{};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = "Game Window Class";
    window_class.lpfnWndProc = window_callback;

    // Register Class
    RegisterClass(&window_class);

    // Create window
    HWND window{CreateWindow(window_class.lpszClassName, "Solar System", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0)};
    HDC hdc{GetDC(window)};

    while (running)
    {
        // Input
        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        // Simulate
        render_background();
        clear_screen(0x00ffa0);
        draw_rect(0.5, 0.5, 0.2, 0.1, 0xff0000);

        // Render
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
        
        
    }

    return 0;
}
