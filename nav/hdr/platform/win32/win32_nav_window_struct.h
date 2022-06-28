#ifndef WIN32_NAV_WINDOW_STRUCT
#define WIN32_NAV_WINDOW_STRUCT

#define LEAN_AND_MEAN

#include <platform/nav_window.h>
#include <Windows.h>

struct WindowType
{
    HWND hWnd;
    HDC hDc;
};


#endif