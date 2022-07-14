#ifndef WIN32_NAV_WINDOW_STRUCT
#define WIN32_NAV_WINDOW_STRUCT

#define LEAN_AND_MEAN

#include <platform/nav_window.h>
#include <windows.h>

#define NAV_WINDOW_STATE_CAN_CLOSE_BIT 0

struct Nav_WindowType
{
    Bit8 state;

    HWND hWnd;
    HDC hDc;
};


#endif